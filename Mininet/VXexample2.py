#!/usr/bin/python

"""
This example shows how to create an empty Mininet object
(without a topology object) and add nodes to it manually.
"""

from mininet.net import Mininet
from mininet.node import RemoteController
from mininet.cli import CLI
from mininet.log import setLogLevel, info

def emptyNet():

    "Create an empty network and add nodes to it."

    net = Mininet( )

    info( '*** Adding controller\n' )



    info( '*** Adding hosts\n' )
    red2 = net.addHost( 'red2', ip='10.0.0.2', mac='00:00:00:00:00:02' )
    blue2 = net.addHost( 'blue2', ip='10.0.0.2', mac='00:00:00:00:00:02' )

    info( '*** Adding switch\n' )
    s2 = net.addSwitch( 's2' )

    info( '*** Creating links\n' )
    net.addLink( red2, s2 )
    net.addLink( blue2, s2 )

    info( '*** Starting network\n')
    net.start()
    print "Host ", red2.name, " has IP address = ", red2.IP(), " and MAC address = ", red2.MAC()
    print "Host ", blue2.name, " has IP address = ", blue2.IP(), " and MAC address = ", blue2.MAC()

    info( '*** Running CLI\n' )
    CLI( net )

    info( '*** Stopping network' )
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    emptyNet()