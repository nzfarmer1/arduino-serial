socat -d -d PTY,link=/tmp/ttysocat0 PTY,link=/tmp/ttysocat1 & disown

# Alternative to use UNIX socket

#socat -d -d PTY,link=/tmp/ttysocat0 UNIX-LISTEN:/tmp/test.sock & disown
