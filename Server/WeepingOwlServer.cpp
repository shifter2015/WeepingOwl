/*WeepingOwl TCP Messenger
Copyright (C) 2022  shifter2015

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Contact information: shiftergamer12@gmail.com
*/
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "23"
#define DEFAULT_BUFLEN 512


void sender(int iSendResult, SOCKET ClientSocket, char* sendbuf, char* serveraddr, HANDLE hConsole) {
	for (;;) {
		SetConsoleTextAttribute(hConsole, 15);
		printf("> ");
		std::cin.getline(sendbuf, DEFAULT_BUFLEN);
		iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
		if (iSendResult == SOCKET_ERROR) {
			SetConsoleTextAttribute(hConsole, 12);
			printf("send failed: %d\n", WSAGetLastError());
			SetConsoleTextAttribute(hConsole, 15);
			closesocket(ClientSocket);
			WSACleanup();
			exit(1);

		}
		SetConsoleTextAttribute(hConsole, 9);
		printf("%s: %s\n", serveraddr, sendbuf);
		SetConsoleTextAttribute(hConsole, 15);
	}

}
void listener(int iResult, SOCKET Socket, char* recvbuf, int recvbuflen, char* clientaddr, HANDLE hConsole) {
	for (;;) {

		try {
			iResult = recv(Socket, recvbuf, recvbuflen, 0);
			if (iResult == -1) {
				SetConsoleTextAttribute(hConsole, 12);
				printf("\nConnection lost");
				SetConsoleTextAttribute(hConsole, 15);
				closesocket(Socket);
				WSACleanup();
				exit(1);
			}
			// printf("\nBytes received: %d\n", iResult);
			SetConsoleTextAttribute(hConsole, 14);
			printf("\n%s: ", clientaddr);
			for (int i = 0; i < DEFAULT_BUFLEN; i++) {
				if (recvbuf[i] == '\0') {
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << std::endl << "> ";
					ZeroMemory(recvbuf, DEFAULT_BUFLEN);
					
					break;
				}
				else {
					std::cout << recvbuf[i];
				}
			}


		}

		catch (const std::exception& e) {

		}



	}
}
int main(int argc, char** argv) {
	std::cout << "WeepingOwl  Copyright (C) 2022  shifter2015\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it,\nunder certain conditions; type `show c' for details." << std::endl;
	if (argc == 3) {
		if (argv[1] == "show" && argv[2] == "w") {
			std::cout << "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY\nAPPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\nHOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\nOF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\nTHE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\nPURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\nIS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\nALL NECESSARY SERVICING, REPAIR OR CORRECTION.";
			exit(0);
		}
		else if (argv[1] == "show" && argv[2] == "c") {
			std::cout << "0. Definitions.\n\n\"This License\" refers to version 3 of the GNU General Public License.\n\n\"Copyright\" also means copyright-like laws that apply to other kinds of\nworks, such as semiconductor masks.\n\n\"The Program\" refers to any copyrightable work licensed under this\nLicense.  Each licensee is addressed as \"you\".  \"Licensees\" and\n\"recipients\" may be individuals or organizations.\n\nTo \"modify\" a work means to copy from or adapt all or part of the work\nin a fashion requiring copyright permission, other than the making of an\nexact copy.  The resulting work is called a \"modified version\" of the\nearlier work or a work \"based on\" the earlier work.\n\nA \"covered work\" means either the unmodified Program or a work based\non the Program.\n\nTo \"propagate\" a work means to do anything with it that, without\npermission, would make you directly or secondarily liable for\ninfringement under applicable copyright law, except executing it on a\ncomputer or modifying a private copy.  Propagation includes copying,\ndistribution (with or without modification), making available to the\npublic, and in some countries other activities as well.\n\nTo \"convey\" a work means any kind of propagation that enables other\nparties to make or receive copies.  Mere interaction with a user through\na computer network, with no transfer of a copy, is not conveying.\n\nAn interactive user interface displays \"Appropriate Legal Notices\"\nto the extent that it includes a convenient and prominently visible\nfeature that (1) displays an appropriate copyright notice, and (2)\ntells the user that there is no warranty for the work (except to the\nextent that warranties are provided), that licensees may convey the\nwork under this License, and how to view a copy of this License.  If\nthe interface presents a list of user commands or options, such as a\nmenu, a prominent item in the list meets this criterion.\n\n1. Source Code.\n\nThe \"source code\" for a work means the preferred form of the work\nfor making modifications to it.  \"Object code\" means any non-source\nform of a work.\n\nA \"Standard Interface\" means an interface that either is an official\nstandard defined by a recognized standards body, or, in the case of\ninterfaces specified for a particular programming language, one that\nis widely used among developers working in that language.\n\nThe \"System Libraries\" of an executable work include anything, other\nthan the work as a whole, that (a) is included in the normal form of\npackaging a Major Component, but which is not part of that Major\nComponent, and (b) serves only to enable use of the work with that\nMajor Component, or to implement a Standard Interface for which an\nimplementation is available to the public in source code form.  A\n\"Major Component\", in this context, means a major essential component\n(kernel, window system, and so on) of the specific operating system\n(if any) on which the executable work runs, or a compiler used to\nproduce the work, or an object code interpreter used to run it.\n\nThe \"Corresponding Source\" for a work in object code form means all\nthe source code needed to generate, install, and (for an executable\nwork) run the object code and to modify the work, including scripts to\ncontrol those activities.  However, it does not include the work's\nSystem Libraries, or general-purpose tools or generally available free\nprograms which are used unmodified in performing those activities but\nwhich are not part of the work.  For example, Corresponding Source\nincludes interface definition files associated with source files for\nthe work, and the source code for shared libraries and dynamically\nlinked subprograms that the work is specifically designed to require,\nsuch as by intimate data communication or control flow between those\nsubprograms and other parts of the work.\n\nThe Corresponding Source need not include anything that users\ncan regenerate automatically from other parts of the Corresponding\nSource.\n\nThe Corresponding Source for a work in source code form is that\nsame work.\n\n2. Basic Permissions.\n\nAll rights granted under this License are granted for the term of\ncopyright on the Program, and are irrevocable provided the stated\nconditions are met.  This License explicitly affirms your unlimited\npermission to run the unmodified Program.  The output from running a\ncovered work is covered by this License only if the output, given its\ncontent, constitutes a covered work.  This License acknowledges your\nrights of fair use or other equivalent, as provided by copyright law.\n\nYou may make, run and propagate covered works that you do not\nconvey, without conditions so long as your license otherwise remains\nin force.  You may convey covered works to others for the sole purpose\nof having them make modifications exclusively for you, or provide you\nwith facilities for running those works, provided that you comply with\nthe terms of this License in conveying all material for which you do\nnot control copyright.  Those thus making or running the covered works\nfor you must do so exclusively on your behalf, under your direction\nand control, on terms that prohibit them from making any copies of\nyour copyrighted material outside their relationship with you.\n\nConveying under any other circumstances is permitted solely under\nthe conditions stated below.  Sublicensing is not allowed; section 10\nmakes it unnecessary.\n\n3. Protecting Users' Legal Rights From Anti-Circumvention Law.\n\nNo covered work shall be deemed part of an effective technological\nmeasure under any applicable law fulfilling obligations under article\n11 of the WIPO copyright treaty adopted on 20 December 1996, or\nsimilar laws prohibiting or restricting circumvention of such\nmeasures.\n\nWhen you convey a covered work, you waive any legal power to forbid\ncircumvention of technological measures to the extent such circumvention\nis effected by exercising rights under this License with respect to\nthe covered work, and you disclaim any intention to limit operation or\nmodification of the work as a means of enforcing, against the work's\nusers, your or third parties' legal rights to forbid circumvention of\ntechnological measures.\n\n4. Conveying Verbatim Copies.\n\nYou may convey verbatim copies of the Program's source code as you\nreceive it, in any medium, provided that you conspicuously and\nappropriately publish on each copy an appropriate copyright notice;\nkeep intact all notices stating that this License and any\nnon-permissive terms added in accord with section 7 apply to the code;\nkeep intact all notices of the absence of any warranty; and give all\nrecipients a copy of this License along with the Program.\n\nYou may charge any price or no price for each copy that you convey,\nand you may offer support or warranty protection for a fee.\n\n5. Conveying Modified Source Versions.\n\nYou may convey a work based on the Program, or the modifications to\nproduce it from the Program, in the form of source code under the\nterms of section 4, provided that you also meet all of these conditions:\n\n  a) The work must carry prominent notices stating that you modified\n  it, and giving a relevant date.\n\n  b) The work must carry prominent notices stating that it is\n  released under this License and any conditions added under section\n  7.  This requirement modifies the requirement in section 4 to\n  \"keep intact all notices\".\n\n  c) You must license the entire work, as a whole, under this\n  License to anyone who comes into possession of a copy.  This\n  License will therefore apply, along with any applicable section 7\n  additional terms, to the whole of the work, and all its parts,\n  regardless of how they are packaged.  This License gives no\n  permission to license the work in any other way, but it does not\n  invalidate such permission if you have separately received it.\n\n  d) If the work has interactive user interfaces, each must display\n  Appropriate Legal Notices; however, if the Program has interactive\n  interfaces that do not display Appropriate Legal Notices, your\n  work need not make them do so.\n\nA compilation of a covered work with other separate and independent\nworks, which are not by their nature extensions of the covered work,\nand which are not combined with it such as to form a larger program,\nin or on a volume of a storage or distribution medium, is called an\n\"aggregate\" if the compilation and its resulting copyright are not\nused to limit the access or legal rights of the compilation's users\nbeyond what the individual works permit.  Inclusion of a covered work\nin an aggregate does not cause this License to apply to the other\nparts of the aggregate.\n\n6. Conveying Non-Source Forms.\n\nYou may convey a covered work in object code form under the terms\nof sections 4 and 5, provided that you also convey the\nmachine-readable Corresponding Source under the terms of this License,\nin one of these ways:\n\n  a) Convey the object code in, or embodied in, a physical product\n  (including a physical distribution medium), accompanied by the\n  Corresponding Source fixed on a durable physical medium\n  customarily used for software interchange.\n\n  b) Convey the object code in, or embodied in, a physical product\n  (including a physical distribution medium), accompanied by a\n  written offer, valid for at least three years and valid for as\n  long as you offer spare parts or customer support for that product\n  model, to give anyone who possesses the object code either (1) a\n  copy of the Corresponding Source for all the software in the\n  product that is covered by this License, on a durable physical\n  medium customarily used for software interchange, for a price no\n  more than your reasonable cost of physically performing this\n  conveying of source, or (2) access to copy the\n  Corresponding Source from a network server at no charge.\n\n  c) Convey individual copies of the object code with a copy of the\n  written offer to provide the Corresponding Source.  This\n  alternative is allowed only occasionally and noncommercially, and\n  only if you received the object code with such an offer, in accord\n  with subsection 6b.\n\n  d) Convey the object code by offering access from a designated\n  place (gratis or for a charge), and offer equivalent access to the\n  Corresponding Source in the same way through the same place at no\n  further charge.  You need not require recipients to copy the\n  Corresponding Source along with the object code.  If the place to\n  copy the object code is a network server, the Corresponding Source\n  may be on a different server (operated by you or a third party)\n  that supports equivalent copying facilities, provided you maintain\n  clear directions next to the object code saying where to find the\n  Corresponding Source.  Regardless of what server hosts the\n  Corresponding Source, you remain obligated to ensure that it is\n  available for as long as needed to satisfy these requirements.\n\n  e) Convey the object code using peer-to-peer transmission, provided\n  you inform other peers where the object code and Corresponding\n  Source of the work are being offered to the general public at no\n  charge under subsection 6d.\n\nA separable portion of the object code, whose source code is excluded\nfrom the Corresponding Source as a System Library, need not be\nincluded in conveying the object code work.\n\nA \"User Product\" is either (1) a \"consumer product\", which means any\ntangible personal property which is normally used for personal, family,\nor household purposes, or (2) anything designed or sold for incorporation\ninto a dwelling.  In determining whether a product is a consumer product,\ndoubtful cases shall be resolved in favor of coverage.  For a particular\nproduct received by a particular user, \"normally used\" refers to a\ntypical or common use of that class of product, regardless of the status\nof the particular user or of the way in which the particular user\nactually uses, or expects or is expected to use, the product.  A product\nis a consumer product regardless of whether the product has substantial\ncommercial, industrial or non-consumer uses, unless such uses represent\nthe only significant mode of use of the product.\n\n\"Installation Information\" for a User Product means any methods,\nprocedures, authorization keys, or other information required to install\nand execute modified versions of a covered work in that User Product from\na modified version of its Corresponding Source.  The information must\nsuffice to ensure that the continued functioning of the modified object\ncode is in no case prevented or interfered with solely because\nmodification has been made.\n\nIf you convey an object code work under this section in, or with, or\nspecifically for use in, a User Product, and the conveying occurs as\npart of a transaction in which the right of possession and use of the\nUser Product is transferred to the recipient in perpetuity or for a\nfixed term (regardless of how the transaction is characterized), the\nCorresponding Source conveyed under this section must be accompanied\nby the Installation Information.  But this requirement does not apply\nif neither you nor any third party retains the ability to install\nmodified object code on the User Product (for example, the work has\nbeen installed in ROM).\n\nThe requirement to provide Installation Information does not include a\nrequirement to continue to provide support service, warranty, or updates\nfor a work that has been modified or installed by the recipient, or for\nthe User Product in which it has been modified or installed.  Access to a\nnetwork may be denied when the modification itself materially and\nadversely affects the operation of the network or violates the rules and\nprotocols for communication across the network.\n\nCorresponding Source conveyed, and Installation Information provided,\nin accord with this section must be in a format that is publicly\ndocumented (and with an implementation available to the public in\nsource code form), and must require no special password or key for\nunpacking, reading or copying.\n\n7. Additional Terms.\n\n\"Additional permissions\" are terms that supplement the terms of this\nLicense by making exceptions from one or more of its conditions.\nAdditional permissions that are applicable to the entire Program shall\nbe treated as though they were included in this License, to the extent\nthat they are valid under applicable law.  If additional permissions\napply only to part of the Program, that part may be used separately\nunder those permissions, but the entire Program remains governed by\nthis License without regard to the additional permissions.\n\nWhen you convey a copy of a covered work, you may at your option\nremove any additional permissions from that copy, or from any part of\nit.  (Additional permissions may be written to require their own\nremoval in certain cases when you modify the work.)  You may place\nadditional permissions on material, added by you to a covered work,\nfor which you have or can give appropriate copyright permission.\n\nNotwithstanding any other provision of this License, for material you"
				"\nadd to a covered work, you may (if authorized by the copyright holders of\nthat material) supplement the terms of this License with terms:\n\n  a) Disclaiming warranty or limiting liability differently from the\n  terms of sections 15 and 16 of this License; or\n\n  b) Requiring preservation of specified reasonable legal notices or\n  author attributions in that material or in the Appropriate Legal\n  Notices displayed by works containing it; or\n\n  c) Prohibiting misrepresentation of the origin of that material, or\n  requiring that modified versions of such material be marked in\n  reasonable ways as different from the original version; or\n\n  d) Limiting the use for publicity purposes of names of licensors or\n  authors of the material; or\n\n  e) Declining to grant rights under trademark law for use of some\n  trade names, trademarks, or service marks; or\n\n  f) Requiring indemnification of licensors and authors of that\n  material by anyone who conveys the material (or modified versions of\n  it) with contractual assumptions of liability to the recipient, for\n  any liability that these contractual assumptions directly impose on\n  those licensors and authors.\n\nAll other non-permissive additional terms are considered \"further\nrestrictions\" within the meaning of section 10.  If the Program as you\nreceived it, or any part of it, contains a notice stating that it is\ngoverned by this License along with a term that is a further\nrestriction, you may remove that term.  If a license document contains\na further restriction but permits relicensing or conveying under this\nLicense, you may add to a covered work material governed by the terms\nof that license document, provided that the further restriction does\nnot survive such relicensing or conveying.\n\nIf you add terms to a covered work in accord with this section, you\nmust place, in the relevant source files, a statement of the\nadditional terms that apply to those files, or a notice indicating\nwhere to find the applicable terms.\n\nAdditional terms, permissive or non-permissive, may be stated in the\nform of a separately written license, or stated as exceptions;\nthe above requirements apply either way.\n\n8. Termination.\n\nYou may not propagate or modify a covered work except as expressly\nprovided under this License.  Any attempt otherwise to propagate or\nmodify it is void, and will automatically terminate your rights under\nthis License (including any patent licenses granted under the third\nparagraph of section 11).\n\nHowever, if you cease all violation of this License, then your\nlicense from a particular copyright holder is reinstated (a)\nprovisionally, unless and until the copyright holder explicitly and\nfinally terminates your license, and (b) permanently, if the copyright\nholder fails to notify you of the violation by some reasonable means\nprior to 60 days after the cessation.\n\nMoreover, your license from a particular copyright holder is\nreinstated permanently if the copyright holder notifies you of the\nviolation by some reasonable means, this is the first time you have\nreceived notice of violation of this License (for any work) from that\ncopyright holder, and you cure the violation prior to 30 days after\nyour receipt of the notice.\n\nTermination of your rights under this section does not terminate the\nlicenses of parties who have received copies or rights from you under\nthis License.  If your rights have been terminated and not permanently\nreinstated, you do not qualify to receive new licenses for the same\nmaterial under section 10.\n\n9. Acceptance Not Required for Having Copies.\n\nYou are not required to accept this License in order to receive or\nrun a copy of the Program.  Ancillary propagation of a covered work\noccurring solely as a consequence of using peer-to-peer transmission\nto receive a copy likewise does not require acceptance.  However,\nnothing other than this License grants you permission to propagate or\nmodify any covered work.  These actions infringe copyright if you do\nnot accept this License.  Therefore, by modifying or propagating a\ncovered work, you indicate your acceptance of this License to do so.\n\n10. Automatic Licensing of Downstream Recipients.\n\nEach time you convey a covered work, the recipient automatically\nreceives a license from the original licensors, to run, modify and\npropagate that work, subject to this License.  You are not responsible\nfor enforcing compliance by third parties with this License.\n\nAn \"entity transaction\" is a transaction transferring control of an\norganization, or substantially all assets of one, or subdividing an\norganization, or merging organizations.  If propagation of a covered\nwork results from an entity transaction, each party to that\ntransaction who receives a copy of the work also receives whatever\nlicenses to the work the party's predecessor in interest had or could\ngive under the previous paragraph, plus a right to possession of the\nCorresponding Source of the work from the predecessor in interest, if\nthe predecessor has it or can get it with reasonable efforts.\n\nYou may not impose any further restrictions on the exercise of the\nrights granted or affirmed under this License.  For example, you may\nnot impose a license fee, royalty, or other charge for exercise of\nrights granted under this License, and you may not initiate litigation\n(including a cross-claim or counterclaim in a lawsuit) alleging that\nany patent claim is infringed by making, using, selling, offering for\nsale, or importing the Program or any portion of it." << std::endl;
			exit(0);
		}

	}
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	std::cout << "You are running WeepingOwl Server release-1.0!\n";
	std::cout << "INFORMATION: 127.0.0.1 is YOU, The IP you are bound to is the client IP.\n";
	std::cout << "If you are running on localhost for testing, client ip may come up as 127.0.0.1\n";
	SetConsoleTextAttribute(hConsole, 15);
	WSADATA wsaData;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("WSAStartup failed: %d\n", iResult);
		SetConsoleTextAttribute(hConsole, 15);
		return 1;
	}
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("getaddrinfo failed: %d\n", iResult);
		SetConsoleTextAttribute(hConsole, 15);
		WSACleanup();
		return 1;
	}
	SOCKET ListenSocket = INVALID_SOCKET;
	// Create a SOCKET for the server to listen for client connections
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("Error at socket(): %ld\n", WSAGetLastError());
		SetConsoleTextAttribute(hConsole, 15);
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("bind failed with error: %d\n", WSAGetLastError());
		SetConsoleTextAttribute(hConsole, 15);
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	char serveraddr[DEFAULT_BUFLEN];
	ZeroMemory(serveraddr, DEFAULT_BUFLEN);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "bound to " << inet_ntop(result->ai_family, result->ai_addr, serveraddr, DEFAULT_BUFLEN) << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	freeaddrinfo(result);
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		SetConsoleTextAttribute(hConsole, 15);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	SOCKET ClientSocket;
	ClientSocket = INVALID_SOCKET;
	//Accept a client socket
	struct sockaddr_in client_addr;
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("accept failed: %d\n", WSAGetLastError());
		SetConsoleTextAttribute(hConsole, 15);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	int addrlen = sizeof(client_addr);
	iResult = getpeername(ClientSocket, (struct sockaddr*)&client_addr, &addrlen);
	if (iResult == SOCKET_ERROR) {
		SetConsoleTextAttribute(hConsole, 12);
		printf("Error at getpeername(): %ld\n", WSAGetLastError());
		SetConsoleTextAttribute(hConsole, 15);
		closesocket(ClientSocket);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	char addrbuf[DEFAULT_BUFLEN];
	ZeroMemory(addrbuf, DEFAULT_BUFLEN);
	SetConsoleTextAttribute(hConsole, 10);
	std::cout << "CONNECTION ESTABILISHED TO " << inet_ntop(client_addr.sin_family, &client_addr.sin_addr, addrbuf, DEFAULT_BUFLEN) << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	char recvbuf[DEFAULT_BUFLEN];
	int iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;
	char sendbuf[DEFAULT_BUFLEN];
	ZeroMemory(recvbuf, DEFAULT_BUFLEN);
	ZeroMemory(sendbuf, DEFAULT_BUFLEN);

	
	std::thread t_listener(&listener, iResult, ClientSocket, recvbuf, recvbuflen, serveraddr, hConsole);
	std::thread t_sender(&sender, iSendResult, ClientSocket, sendbuf, addrbuf, hConsole);
	t_listener.join();
	t_sender.join();
	// cleanup
	SetConsoleTextAttribute(hConsole, 15);
	closesocket(ClientSocket);
	WSACleanup();
	return 0;
}
