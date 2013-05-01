####Git Config
- Checking the project out: `git clone https://[GitUserName]@github.com/msartintarm/bashers5.git .`
- Rebase from remote branches by default: `git config --global branch.autosetuprebase remote`
- Enable color highlighting by default: `git config --global color.ui "auto"`
- We don't really care about whitespace in our files - tell Git to ignore it. `git config --global apply.whitespace nowarn`

Last 3 configs have to be redone for each computer (not that they're necessary to work). 

You can run the script [git-config.sh](git-config.sh), which does this automatically.
