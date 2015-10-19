SSH SERVER-CLIENT RSA KEY CONFIGURATION
find ~/.ssh
chmod RWX------ permissions

ssh-keygen -t rsa [-b 2048]
Enter file in which to save the key
Enter passphrase (empty for no passphrase)
Enter same passphrase again

ssh-copy-id odroid@hostname
