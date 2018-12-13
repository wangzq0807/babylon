set (PAXOS_SRCS
    paxos.cxx
    socket.cxx
    )

add_executable (paxos
    ${PAXOS_SRCS}
)

add_executable (client
    socket.cxx
    client.cxx)
