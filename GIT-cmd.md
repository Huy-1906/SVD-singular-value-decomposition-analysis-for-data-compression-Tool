## GIT Command
<table>
  <tr>
    <th>Command</th>
    <th>Significance</th>
  </tr>
  <tr>
    <td>git init</td>
    <td>Initializes a new Git repository in the current directory</td>
  </tr>
  <tr>
    <td>git clone [url]</td>
    <td>Clones a remote repository to your computer</td>
  </tr>
  <tr>
    <td>git add [file/.]</td>
    <td>Adds file to the staging area, preparing it for commit</td >
  </tr>
  <tr>
    <td>git commit</td>
    <td>Your commit</td >
  </tr>
  <tr>
    <td>git status</td>
    <td>Shows the status of files in the working directory and staging area</td>
  </tr>
  <tr>
    <td>git log</code</td>
    <td> Displays the commit history of the repository</td>
  </tr>
  <tr>
    <td>git pull</code</td>
    <td>Fetches changes from the remote repository and merges them into the current branch</td>
  </tr>
  <tr>
    <td>git push</code</td>
    <td> Pushes changes from the current branch to the remote repository</td>
  </tr>
  <tr>
    <td>git fetch</code</td>
    <td>Fetches changes from the remote repository without merging them into the current branch</td>
  </tr>
  <tr>
    <td>git checkout [brand]</code</td>
    <td>Lists branches or creates a new branch</td>
  </tr>
  <tr>
    <td>git rebase [branch]</code</td>
    <td>Rebases the commits of the current branch onto the specified branch</td>
  </tr>
</table>


<hr>

### How to create and push a new branch
1. Create a new branch
    ```sh
    git checkout -b mem/apt
    ```
    * Create a new branch named <code>mem/apt</code>
    * Switch to mem/apt branch.

2. Push New Branch to Repository
    ```sh
    git push --set-upstream origin mem/apt
    ```
    * Push the <code>mem/apt</code> branch to the remote repository named <code>origin</code>
    * Upstream setup

    -> The following <code>git pull</code> and <code>git push</code> commands will automatically work with the <code>mem/apt</code> branch.
3. Update main branch
    ```sh
    git stash
    git checkout main
    ```
    * <code>git stash</code> stores changes to a stash stack and you can reapply them later
    * If you have committed or stashed your changes, you can then switch to the main branch

    ```sh
    git rebase mem/apt
    ```
    * Rebase the commit history of the current branch based on the <code>mem/apt</code> branch

    ```sh
    git push
    ```
    --> Push changes from the master branch to the repository

