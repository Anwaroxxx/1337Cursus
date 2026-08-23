#!/bin/bash
#
# monitoring.sh - broadcasts server stats to all terminals (see `man wall`)
# Installed as /usr/local/bin/monitoring.sh, scheduled every 10 min via cron.

LC_ALL=C

arc=$(uname -a)

pcpu=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)

vcpu=$(grep -c "^processor" /proc/cpuinfo)

ram_total=$(free -m | awk '$1 == "Mem:" {print $2}')
ram_used=$(free -m | awk '$1 == "Mem:" {print $3}')
ram_pct=$(awk -v u="$ram_used" -v t="$ram_total" 'BEGIN {printf "%.2f", u / t * 100}')

disk_total=$(df -h --total | awk '$1 == "total" {print $2}')
disk_used=$(df -m --total | awk '$1 == "total" {print $3}')
disk_pct=$(df --total | awk '$1 == "total" {gsub(/%/, "", $5); print $5}')

cpu_load=$(top -bn1 | grep '^%Cpu' | awk '{printf "%.1f", 100 - $8}')

last_boot=$(who -b | awk '{print $3" "$4}')

if [ "$(lsblk | grep -c 'lvm')" -gt 0 ]; then
	lvm_use="yes"
else
	lvm_use="no"
fi

tcp_estab=$(ss -tan | grep -c ESTAB)

user_log=$(who | wc -l)

ipv4=$(ip -o -4 addr show scope global | awk '{print $4}' | cut -d/ -f1 | head -1)
mac=$(ip link show | awk '$1 == "link/ether" {print $2}' | head -1)

sudo_cmd=$(journalctl -q _COMM=sudo | grep -c COMMAND)

msg="	#Architecture: $arc
	#CPU physical : $pcpu
	#vCPU : $vcpu
	#Memory Usage: $ram_used/${ram_total}MB ($ram_pct%)
	#Disk Usage: $disk_used/${disk_total}b ($disk_pct%)
	#CPU load: $cpu_load%
	#Last boot: $last_boot
	#LVM use: $lvm_use
	#Connections TCP : $tcp_estab ESTABLISHED
	#User log: $user_log
	#Network: IP $ipv4 ($mac)
	#Sudo : $sudo_cmd cmd"

wall "$msg"
