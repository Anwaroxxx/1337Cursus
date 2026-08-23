# Born2beRoot — Defense Cheat Sheet

Quick answers to the questions evaluators actually ask. Understand each one,
do not memorize blindly.

## OS basics

**Debian vs Rocky?** Debian uses `apt`/`aptitude` and **AppArmor**; Rocky
(RHEL family) uses `dnf/yum` and **SELinux**. Debian is simpler, recommended
for a first sysadmin project.

**apt vs aptitude?** Both are package managers on top of APT.
- `apt` = CLI tool, lighter, default for scripts.
- `aptitude` = interactive front-end with an ncurses UI and better conflict
  resolution (proposes removals/holds when dependencies clash).

**What is AppArmor?** Mandatory Access Control security module (Linux Security
Module). Programs are confined by *profiles* defining which files/capabilities
they may touch, even if they get compromised. Check: `aa-status`.

**What is SELinux?** Same idea as AppArmor (MAC), used by RHEL/Rocky:
labels every object with security contexts and enforces policy rules.
(AppArmor attaches profiles to paths, SELinux to inodes/labels.)

## LVM & partitions

**What is LVM?** Logical Volume Manager: abstraction layer between disks and
filesystems — Physical Volumes → Volume Group → Logical Volumes. Lets you
resize/move/add storage without repartitioning.

**Why encrypt + LVM?** The physical partition is encrypted (dm-crypt/LUKS);
at boot a passphrase decrypts it, then LVM carves flexible LVs out of it.

**How does decryption happen at boot?** The initramfs asks for the passphrase,
opens the device with dm-crypt (`cryptsetup`), which exposes `/dev/mapper/...`
that GRUB/kernel then mount via LVM.

**Check:** `lsblk`, `sudo vgs`, `sudo lvs`, `df -h`.

## Users, groups, passwords

**Where are users/groups stored?** `/etc/passwd` (users), `/etc/shadow`
(hashed passwords), `/etc/group`. Hashing: SHA512 via crypt in shadow.

**Password rules implemented?** Expiry 30d, min 2d before change, warning 7d
(`login.defs` + `chage -l user`); length ≥10, upper+lower+digit, max 3
repeated chars, no username, difok 7 not applied to root (`pam_pwquality`).

**Create a new user in group X at defense:**

```bash
sudo useradd -m newuser -g user42      # or adduser
sudo usermod -aG sudo,newgroup existinguser
groups newuser
```

## Sudo

**What is sudo?** Execute commands as another user (usually root) with
per-user permission rules from `/etc/sudoers` (edit only via `visudo`).
su switches identity entirely; sudo keeps your account, logs actions.

**Our strict config:** 3 tries (`passwd_tries`), custom error message
(`badpass_message`), inputs+outputs archived in `/var/log/sudo`
(`log_input, log_output`, `iolog_dir`), TTY enforced (`requiretty`/`use_pty`),
restricted PATH (`secure_path`). Check logs: `ls /var/log/sudo`,
`journalctl _COMM=sudo | grep COMMAND`.

**Why secure_path?** Prevents running malicious binaries placed in
attacker-controlled directories via hijacked `$PATH` (Trojan horse attack).

## SSH

**What is SSH?** Encrypted remote shell protocol (client-server). We run
OpenSSH server on port **4242**, root login forbidden
(`PermitRootLogin no`). Config: `/etc/ssh/sshd_config`, restart with
`systemctl restart ssh`. Test from host:
`ssh -p 4242 anwar@<vm-ip>`.

**Why a non-standard port?** Reduces exposure to mass automated scans/bots
targeting port 22 (security by obscurity, layered with keys/firewall).

**Public vs private key?** Private stays on the client (never shared), public
goes to servers' `~/.ssh/authorized_keys`; auth proves possession of private
key without sending it.

## UFW

**What is UFW?** Uncomplicated Firewall — friendly front-end to netfilter
(iptables/nftables). Stateful packet filtering: allow/deny by port/source.

```bash
sudo ufw status        # active, only 4242 allowed
sudo ufw allow 4242
sudo ufw deny <port>
```

## cron / monitoring.sh

**What is cron?** Daemon reading crontabs (`/etc/crontab`,
`/var/spool/cron/*`) that schedules commands: `min hour day month weekday`.
Our entry: `*/10 * * * * /usr/local/bin/monitoring.sh` (+ `@reboot`), so the
script runs every 10 minutes as root and broadcasts stats with `wall`.
Stop without editing: `sudo systemctl stop cron` (restart: `start`).

**Script internals (know every line!):**
- architecture/kernel: `uname -a`
- physical CPUs: unique `physical id` in `/proc/cpuinfo`; virtual = `processor` entries
- RAM: `free -m` (used/total, %)
- disk: `df --total` (used/total, Use%)
- CPU load: `top -bn1`, 100 − idle%
- last boot: `who -b`; LVM active: grep lvm in `lsblk`
- TCP established: `ss -tan | grep -c ESTAB`; logged users: `who | wc -l`
- IPv4/MAC: `ip -o -4 addr`, `ip link show`
- sudo count: `journalctl _COMM=sudo`

## Misc questions

**Init/systemd?** PID 1 is systemd: starts services (units) in parallel at
boot, manages dependencies, logging (journald), etc. Check boot target:
`systemctl get-default` (graphical.target would mean GUI installed — we use
multi-user.target).

**Docker vs VM?** VMs virtualize hardware with their own kernel (isolation,
heavyweight); Docker shares host kernel via namespaces/cgroups (light,
fast, less isolated).

**Difference between apt update and upgrade?** `update` refreshes package
index; `upgrade` installs available newer versions of installed packages.
