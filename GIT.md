####Git Config
- Checking the project out: `git clone GitHubUserName@https://github.com/msartintarm/bashers5.git .`
- All commits get pushed to their upstream remote branch: `git config --global push.default upstream`
- Rebase from remote branches by default: `git config --global branch.autosetuprebase remote`
- Enable color highlighting by default: `git config --global color.ui "auto"`
- We don't really care about whitespace in our files - tell Git to ignore it. `git config --global apply.whitespace nowarn`
