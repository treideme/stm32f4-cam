# How to work with this

Fork this repository into a new bitbucket repository.

Then add this repository as upstream.

$ git remote add upstream ssh://git@bitbucket.org:<upstream>/<repo>.git
$ git fetch <remote_name>
$ git checkout master

Merge changes from the template to
$ git merge remotes/upstream/master
