set (PAXOS_SRCS
    paxos.cxx
    socket.cxx
    epoller.cxx
    channel.cxx
    tcpconnection.cxx
    eventloop.cxx
    )

add_executable (paxos
    ${PAXOS_SRCS}
)

add_executable (client
    socket.cxx
    client.cxx)
