// IBM Legacy FORTRAN VS Code integration.
// Bridges the editor to the ibm-fortran-tool analyzer and ibm-fortran-app runner.
const vscode = require('vscode');
const cp = require('child_process');
const path = require('path');

function workspaceFolderUri(document) {
  const folder = vscode.workspace.getWorkspaceFolder(document.uri);
  return folder ? folder.uri.fsPath : path.dirname(document.uri.fsPath);
}

function runTool(configKey, args, cwd) {
  const executable = vscode.workspace.getConfiguration('ibmLegacyFortran').get(configKey);
  return new Promise((resolve, reject) => {
    cp.execFile(executable, args, { cwd }, (error, stdout, stderr) => {
      if (error && error.code !== 1) {
        reject(new Error(stderr || error.message));
        return;
      }
      resolve({ stdout: stdout || '', stderr: stderr || '' });
    });
  });
}

async function analyze(document, diagnostics) {
  if (document.languageId !== 'fortran-ibmlegacy') {
    return;
  }
  let result;
  try {
    result = await runTool('toolPath', [document.uri.fsPath, '--json'], workspaceFolderUri(document));
  } catch (error) {
    vscode.window.showWarningMessage(`IBM FORTRAN tool failed: ${error.message}`);
    diagnostics.set(document.uri, []);
    return;
  }
  let report;
  try {
    report = JSON.parse(result.stdout.trim());
  } catch (parseError) {
    diagnostics.set(document.uri, []);
    return;
  }
  const severityMap = {
    error: vscode.DiagnosticSeverity.Error,
    warning: vscode.DiagnosticSeverity.Warning,
    note: vscode.DiagnosticSeverity.Information
  };
  const items = (report.findings || []).map((finding) => {
    const line = Math.max(0, (finding.line || 1) - 1);
    const range = new vscode.Range(line, 0, line, Number.MAX_SAFE_INTEGER);
    const diagnostic = new vscode.Diagnostic(range, `[${finding.code}] ${finding.message}`, severityMap[finding.severity] || vscode.DiagnosticSeverity.Information);
    diagnostic.source = 'ibm-fortran-tool';
    return diagnostic;
  });
  diagnostics.set(document.uri, items);
}

function activate(context) {
  const diagnostics = vscode.languages.createDiagnosticCollection('ibmFortran');
  context.subscriptions.push(diagnostics);

  const analyzeActive = () => {
    const editor = vscode.window.activeTextEditor;
    if (editor) {
      analyze(editor.document, diagnostics);
    }
  };

  context.subscriptions.push(vscode.commands.registerCommand('ibmLegacyFortran.analyzeFile', analyzeActive));

  context.subscriptions.push(vscode.commands.registerCommand('ibmLegacyFortran.runFile', async () => {
    const editor = vscode.window.activeTextEditor;
    if (!editor) {
      return;
    }
    try {
      const result = await runTool('runnerPath', [editor.document.uri.fsPath], workspaceFolderUri(editor.document));
      const output = vscode.window.createOutputChannel('IBM FORTRAN');
      output.clear();
      output.appendLine(`> ${path.basename(editor.document.uri.fsPath)}`);
      if (result.stdout) {
        output.appendLine(result.stdout.replace(/\n$/, ''));
      }
      if (result.stderr) {
        output.appendLine(result.stderr.replace(/\n$/, ''));
      }
      output.show(true);
    } catch (error) {
      vscode.window.showErrorMessage(`IBM FORTRAN runner failed: ${error.message}`);
    }
  }));


  context.subscriptions.push(vscode.workspace.onDidSaveTextDocument((document) => analyze(document, diagnostics)));
  context.subscriptions.push(vscode.workspace.onDidOpenTextDocument((document) => analyze(document, diagnostics)));
  context.subscriptions.push(vscode.workspace.onDidCloseTextDocument((document) => diagnostics.delete(document.uri)));
}

function deactivate() { }

module.exports = { activate, deactivate };
