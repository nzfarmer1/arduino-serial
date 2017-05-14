#socat -d -d PTY,link=/tmp/ttysocat0 PTY,link=/tmp/ttysocat1 & disown

# Alternative to use UNIX socket
rm -f /tmp/test.sock /tmp/ttysocat0

#socat -d -d PTY,link=/tmp/ttysocat0 UNIX-LISTEN:/tmp/test.sock & disown
while true
do
	socat -d -d PTY,link=/tmp/ttysocat0,unlink-close=0 UNIX-LISTEN:/tmp/test.sock,fork,reuseaddr
	sleep 1
done
