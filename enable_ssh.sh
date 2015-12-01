# First add network adapter eth1 (second adapter) "Bridged" in VirtualBox
# Then change /etc/network/interfaces like below
# http://wiredrevolution.com/virtualbox/setup-ssh-access-between-virtualbox-host-and-guest-vms
if grep -xq ".*eth1.*" /etc/network/interfaces; then
	# May need to change the assigned static IP to avoid conflict
	cat interfaces | sudo tee -a /etc/network/interfaces
fi
# sudo this file!
sudo apt-get install openssh-server
sudo service ssh start
