# Born2beRoot — Setup Guide (Debian)

Step-by-step checklist covering every mandatory requirement of the subject.
OS choice: **latest stable Debian** (recommended), no GUI. Do everything in
order — later steps depend on earlier ones.

## 1. Virtual machine

1. Create a new VirtualBox VM: type Linux, Debian (64-bit).
2. Recommended disk: **30.8 GB** (needed for the LVM bonus structure to fit),
   dynamically allocated.
3. Attach the Debian netinst ISO and boot.
4. Install **without any graphical environment**: uncheck everything in
   tasksel except *SSH server* and *standard system utilities*.
5. During install set:
   - hostname: your login ending with `42` (e.g. `anwar42`)
   - root password (must already respect the policy below)
   - user = your intra login (e.g. `anwar`)

## 2. Encrypted LVM partitions

In the Debian installer, at the partitioning step choose **Manual**, then:

1. Select the disk → create a new partition table.
2. Partition 1: **/boot** — primary, `500 MB`, ext4, mount point `/boot`,
   bootable flag.
3. Rest of the disk: one partition used as **physical volume for encryption**
   (passphrase will be asked at every boot).
4. Inside `Encrypted volume (sda2_crypt)` → configure as a physical volume,
   then create a **volume group** named e.g. `LVMGroup`.
5. Create logical volumes (+ ext4 filesystems) inside it:

| LV | size | mount |
| --- | --- | --- |
| `root` | 10 GB | `/` |
| `swap` | 2.3 GB | swap |
| `home` | 5 GB | `/home` |
| `var` | 3 GB | `/var` |
| `srv` | 3 GB | `/srv` |
| `tmp` | 3 GB | `/tmp` |
| `var-log` | rest (~4 GB) | `/var/log` |

Verify after boot:

```bash
lsblk                    # sda2 must show crypt -> LVMGroup-*
```

## 3. Sudo

```bash
apt-get update && apt-get upgrade -y
apt-get install -y sudo vim git curl ufw
```

Configure with strict rules:

```bash
mkdir -p /var/log/sudo
visudo
```

Add under the existing `Defaults` lines:

```
Defaults	passwd_tries=3
Defaults	badpass_message="Wrong password. Try again."
Defaults	logfile="/var/log/sudo/log"
Defaults	log_input, log_output
Defaults	iolog_dir=/var/log/sudo
Defaults	requiretty
Defaults	secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
Defaults	use_pty
```

> If `visudo -c` reports `requiretty` unknown on your sudo version, remove
> that line only (`use_pty` provides the TTY security). Test config always
> with `visudo -c`.

## 4. User & groups

```bash
usermod -aG sudo,user42 anwar    # your login
groups anwar                     # must list sudo and user42
groupadd user42                  # only if not created earlier
```

## 5. Strong password policy

### Expiration (`/etc/login.defs`)

```
PASS_MAX_DAYS	30
PASS_MIN_DAYS	2
PASS_WARN_AGE	7
```

Apply to **existing** accounts too (login.defs only affects new users):

```bash
chage -M 30 -m 2 -W 7 anwar
chage -M 30 -m 2 -W 7 root
chage -l anwar        # verify
```

### Quality (`pam_pwquality`)

Edit `/etc/pam.d/common-password`, on the `pam_pwquality.so` line add:

```
retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 usercheck=1 difok=7 enforcing=1
```

Same options can be mirrored in `/etc/security/pwquality.conf`.
Notes: `difok=7` (7 chars different from previous password) does **not**
apply to root by design; `usercheck=1` rejects passwords containing the
username.

### Rotate all passwords

After configuring, change the password of **every account including root**:

```bash
passwd
sudo passwd root
sudo passwd anwar
```

New passwords must satisfy: ≥ 10 chars, uppercase + lowercase + digit, no
more than 3 consecutive identical chars, not containing the username.

## 6. SSH on port 4242

Edit `/etc/ssh/sshd_config`:

```
Port 4242
PermitRootLogin no
```

```bash
systemctl restart ssh
systemctl status ssh          # active (running)
ss -tan | grep 4242           # listening
```

Root login over SSH is now impossible.

## 7. UFW firewall

```bash
ufw allow 4242
ufw enable
ufw status                    # only 4242 open
```

UFW must start at boot (default when enabled).

## 8. Hostname

Already set at install; to change later:

```bash
hostnamectl set-hostname anwar42     # evaluators may ask to rename live
vim /etc/hosts                       # update the 127.0.1.1 line too
reboot
```

## 9. monitoring.sh

Copy the script from this repo into the VM (via SSH scp or shared folder):

```bash
scp -P 4242 monitoring.sh anwar@localhost:/tmp
sudo mv /tmp/monitoring.sh /usr/local/bin/
sudo chmod +x /usr/local/bin/monitoring.sh
```

Schedule it with cron (**root crontab**):

```bash
sudo crontab -u root -e
```

```
*/10 * * * * /usr/local/bin/monitoring.sh
@reboot     /usr/local/bin/monitoring.sh
```

Test: wait or `sudo run-parts --report /etc/cron.hourly`, then check tty.
During the defense you will be asked to **stop it without modifying the
script** — answer: `sudo systemctl stop cron`.

## 10. Signature (submission)

Shut down the VM cleanly (so the vdi hash is stable), then on the host:

```bash
cd ~/VirtualBox\ VMs/Born2beRoot/
sha1sum *.vdi > /path/to/repo/born2beroot/signature.txt
```

Only `signature.txt` belongs in the Git repository. After your first defense
clone/duplicate the VM so the hash keeps matching.

## 11. Bonus ideas

- The partition table above already matches the bonus layout.
- WordPress site: `lighttpd` + `MariaDB` + PHP (`php-fpm`/`php-cgi`),
  open port 80 in UFW for it.
- Extra service suggestion: **fail2ban** (brute-force protection) — easy to
  justify during defense; adapt UFW rules accordingly.
