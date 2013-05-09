/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2012 University of British Columbia, Vancouver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Alexander Schloegl <alexander.schloegl@gmx.de>
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

#include <ns3/core-module.h>
#include <ns3/nstime.h>
#include <ns3/simulator.h>
#include <ns3/output-stream-wrapper.h>
#include "ns3/plc.h"

using namespace ns3;

void
ReceiveSuccess(Ptr<const Packet> p)
{
	NS_LOG_UNCOND(Simulator::Now() << ": Packet received!");
}


int main (int argc, char *argv[])
{
// Define spectrum model
    PLC_SpectrumModelHelper smHelper;
    Ptr<const SpectrumModel> sm;
    sm = smHelper.GetSpectrumModel(0, 10e6, 100);

// Create cable types
	Ptr<PLC_Cable> cable = CreateObject<PLC_NAYY150SE_Cable> (sm);

	// Create nodes
	Ptr<PLC_Node> n1 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n2 = CreateObject<PLC_Node> ();
	Ptr<PLC_Node> n3 = CreateObject<PLC_Node> ();
	n1->SetPosition(0,0,0);
	n2->SetPosition(500,0,0);
	n3->SetPosition(1000,0,0);

	PLC_NodeList nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);
	nodes.push_back(n3);

	// Link nodes
	CreateObject<PLC_Line> (cable, n1, n2);
	CreateObject<PLC_Line> (cable, n2, n3);

	// Set up channel
	PLC_ChannelHelper channelHelper(sm);
	channelHelper.Install(nodes);
	Ptr<PLC_Channel> channel = channelHelper.GetChannel();

	PLC_ColoredNoiseFloor CNF;
	CNF->PLC_ColoredNoiseFloor(2,3,4,sm);
	Ptr<SpectrumValue> Vect;
	*Vect PLC_ColoredNoiseFloor::GetNoisePsd();

	// Start simulation
	Simulator::Run();

	// Cleanup simulation
	Simulator::Destroy();

	return EXIT_SUCCESS;

}

