# Editor and IDE integration

Editor/IDE support for the educational fixed-form FORTRAN subset. These files are
independently written project assets; they are not IBM editor plugins.

## Contents
- `vscode/`: a complete VS Code extension with TextMate syntax highlighting,
  language configuration, snippets, diagnostics and command hooks.
- `vim/`: a Vim syntax file.
- `sublime/`: a Sublime Text `.sublime-syntax` grammar.
- `textmate/fortran-ibmlegacy.tmLanguage.json`: a shared TextMate grammar for
  other editors (Atom, TextMate, etc.). The VS Code extension bundles an
  equivalent grammar under `vscode/syntaxes/`.

## VS Code extension
The extension surfaces two commands:

- `IBM FORTRAN: Analyze current file` runs `ibm-fortran-tool --json` and renders
  findings as diagnostics in the Problems panel.
- `IBM FORTRAN: Run current file` executes `ibm-fortran-app` and shows output in
  the `IBM FORTRAN` output channel.

Settings:

- `ibmLegacyFortran.toolPath`: path to `ibm-fortran-tool` (default `ibm-fortran-tool`).
- `ibmLegacyFortran.runnerPath`: path to `ibm-fortran-app` (default `ibm-fortran-app`).

To use the extension from source, open `editors/vscode` in VS Code and press `F5`
to launch an Extension Development Host. Point `toolPath`/`runnerPath` at the
built executables (for example `bin/Debug/ibm-fortran-tool.exe`), or add the
`bin` directory to `PATH`.

## Vim
Copy `vim/fortran-ibmlegacy.vim` to `~/.vim/syntax/` and register the file type:

```vim
au BufRead,BufNewFile *.f,*.for,*.ftn,*.f77 set filetype=fortran-ibmlegacy
```

## Sublime Text
Copy `sublime/fortran-ibmlegacy.sublime-syntax.yaml` into your `Packages/User/`
directory (rename the extension to `.sublime-syntax`).
