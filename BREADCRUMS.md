## Symlinkin pthon3 to python

Open the Terminal by going to Applications > Utilities > Terminal.

Type the following command to create a symbolic link for python that points to python3:


`ln -s /usr/local/bin/python3 /usr/local/bin/python`

Press Enter to create the symbolic link.

Type the following command to check that the symlink was created successfully:


`ls -l /usr/local/bin/python`

You should see output similar to the following, indicating that the symlink was created successfully:

`lrwxr-xr-x  1 username  admin  11 Dec 7 14:32 /usr/local/bin/python -> /usr/local/bin/python3`

To test that the symlink is working, type the following command in the Terminal:

`python --version`

You should see output similar to the following, indicating that python3 is being executed when you type python in the Terminal:

`Python 3.9.1`

You can now use the python command in the Terminal to run python3.
