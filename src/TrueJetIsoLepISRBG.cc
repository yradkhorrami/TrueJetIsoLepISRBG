#include "TrueJetIsoLepISRBG.h"
TrueJetIsoLepISRBG aTrueJetIsoLepISRBG ;

TrueJetIsoLepISRBG::TrueJetIsoLepISRBG() : Processor("TrueJetIsoLepISRBG")
{

	// modify processor description
	_description = "TrueJetIsoLepISRBG does whatever it does ..." ;


	// register steering parameters: name, description, class-variable, default value


	// Inputs: MC-particles, Reco-particles, the link between the two

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"inputPFOCollection" ,
					"Name of the input PFO collection"  ,
					m_inputPFOCollection ,
					std::string("PandoraPFOs")
				);

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"inputIsoLepCollection" ,
					"Name of the input Isolated Leptons collection"  ,
					m_inputIsoLepCollection ,
					std::string("ISOLeptons")
				);

	registerOutputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"outputJetCollection" ,
					"Name of the output Jet collection"  ,
					m_outputJetCollection ,
					std::string("trueJetCollection")
				);

	registerOutputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"outputIsolatedLeptonCollection" ,
					"Name of the output Isolated Lepton collection"  ,
					m_outputIsolatedLeptonCollection ,
					std::string("trueIsolatedLeptons")
				);

	registerOutputCollection( 	LCIO::MCPARTICLE,
					"outputTrueIsolatedLeptonCollection" ,
					"Name of the output True Isolated Lepton collection"  ,
					m_outputTrueIsolatedLeptonCollection ,
					std::string("TrueIsoLeps")
				);

	registerOutputCollection( 	LCIO::MCPARTICLE,
					"outputTrueQuarkCollection" ,
					"Name of the output True Quark collection"  ,
					m_outputTrueQuarkCollection ,
					std::string("TrueQuarks")
				);

	registerOutputCollection( 	LCIO::MCPARTICLE,
					"outputTrueISRCollection" ,
					"Name of the output True ISR photon collection"  ,
					m_outputTrueISRCollection ,
					std::string("TrueISRs")
				);

	registerOutputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"outputRecoISRCollection" ,
					"Name of the output Reconstructed ISR photon collection"  ,
					m_outputRecoISRCollection ,
					std::string("RecoISRs")
				);

	registerOutputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"outputPFOCollection" ,
					"Name of the output PFO collection minus Isolated Leptons and ISR"  ,
					m_outputPFOCollection ,
					std::string("refinedPFOs")
				);

	registerOutputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"outputBackgroundCollection" ,
					"Name of the Background collection (not from jets/ISR/IsolatedLeptons)"  ,
					m_outputBackgroundCollection ,
					std::string("Backgrounds")
				);

	registerProcessorParameter(	"cheatIsoLepton",
					"Whether use MCTruth information to tag Isolated Leptons or not, true = use MCTruth information, false = do not use MCTruth information",
					m_cheatIsoLepton,
					bool(true)
				);

	registerProcessorParameter(	"cheatIsoLeptonFSR",
					"Whether associate FSR photons to Isolated Leptons using MCTruth information or not, true = associate using MCTruth information, false = do not associate",
					m_cheatIsoLeptonFSR,
					bool(true)
				);

	registerProcessorParameter(	"cheatISR",
					"Whether isolate ISR photons using MCTruth information or not, true = isolate ISR photons, false = do not isolate",
					m_cheatISR,
					bool(true)
				);

	registerProcessorParameter(	"cheatOverlay",
					"Whether reject PFOs from other sources to output PFO collection or not, true = reject background by cheating overlay, false = merge backgrounds to putput PFO collection",
					m_cheatOverlay,
					bool(true)
				);


	// Inputs: True jets (as a recoparticle, will be the sum of the _reconstructed particles_
	// created by the true particles in each true jet, in the RecoMCTruthLink sense.
	// link jet-to-reco particles, link jet-to-MC-particles.

	registerInputCollection( 	LCIO::LCRELATION,
					"MCTruthRecoLink",
					"Name of the MCTruthRecoLink input collection"  ,
					_MCTruthRecoLink,
					std::string("MCTruthRecoLink")
				);

	registerInputCollection( 	LCIO::MCPARTICLE,
					"MCParticleCollection" ,
					"Name of the MCParticle collection"  ,
					_MCParticleColllectionName ,
					std::string("MCParticlesSkimmed")
					);

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"RecoParticleCollection" ,
					"Name of the ReconstructedParticles input collection"  ,
					_recoParticleCollectionName ,
					std::string("PandoraPFOs")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"RecoMCTruthLink",
					"Name of the RecoMCTruthLink input collection"  ,
					_recoMCTruthLink,
					std::string("RecoMCTruthLink")
				);

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"TrueJets" ,
					"Name of the TrueJetCollection input collection",
					_trueJetCollectionName ,
					std::string("TrueJets")
				);

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"FinalColourNeutrals" ,
					"Name of the FinalColourNeutralCollection input collection"  ,
					_finalColourNeutralCollectionName ,
					std::string("FinalColourNeutrals")
				);

	registerInputCollection( 	LCIO::RECONSTRUCTEDPARTICLE,
					"InitialColourNeutrals" ,
					"Name of the InitialColourNeutralCollection input collection"  ,
					_initialColourNeutralCollectionName ,
					std::string("InitialColourNeutrals")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"TrueJetPFOLink" ,
					"Name of the TrueJetPFOLink input collection"  ,
					_trueJetPFOLink,
					std::string("TrueJetPFOLink")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"TrueJetMCParticleLink" ,
					"Name of the TrueJetMCParticleLink input collection"  ,
					_trueJetMCParticleLink,
					std::string("TrueJetMCParticleLink")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"FinalElementonLink rueJetMCParticleLink" ,
					"Name of the  FinalElementonLink input collection"	,
					_finalElementonLink,
					std::string("FinalElementonLink")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"InitialElementonLink" ,
					"Name of the  InitialElementonLink input collection"  ,
					_initialElementonLink,
					std::string("InitialElementonLink")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"FinalColourNeutralLink" ,
					"Name of the  FinalColourNeutralLink input collection"  ,
					_finalColourNeutralLink,
					std::string("FinalColourNeutralLink")
				);

	registerInputCollection( 	LCIO::LCRELATION,
					"InitialColourNeutralLink" ,
					"Name of the  InitialColourNeutralLink input collection"  ,
					_initialColourNeutralLink,
					std::string("InitialColourNeutralLink")
				);

}

void TrueJetIsoLepISRBG::init()
{
	streamlog_out(DEBUG9) << "   init called  " << std::endl ;
	printParameters() ;
}

void TrueJetIsoLepISRBG::processRunHeader()
{

}

void TrueJetIsoLepISRBG::processEvent( LCEvent* pLCEvent)
{
	LCCollection *pfoCollection{};
	LCCollection *isoLepCollection{};

	IMPL::LCCollectionVec* outputPfoCollection(NULL);
	outputPfoCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	outputPfoCollection->setSubset( true );
	IMPL::LCCollectionVec* outputJetCollection(NULL);
	outputJetCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	//outputJetCollection->setSubset( true );
	IMPL::LCCollectionVec* outputIsoLepCollection(NULL);
	outputIsoLepCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	outputIsoLepCollection->setSubset( true );
	IMPL::LCCollectionVec* outputTrueIsolateLeptonCollection(NULL);
	outputTrueIsolateLeptonCollection = new IMPL::LCCollectionVec( LCIO::MCPARTICLE );
	outputTrueIsolateLeptonCollection->setSubset( true );
	IMPL::LCCollectionVec* outputTrueQuarkCollection(NULL);
	outputTrueQuarkCollection = new IMPL::LCCollectionVec( LCIO::MCPARTICLE );
	outputTrueQuarkCollection->setSubset( true );
	IMPL::LCCollectionVec* outputTrueISRCollection(NULL);
	outputTrueISRCollection = new IMPL::LCCollectionVec( LCIO::MCPARTICLE );
	outputTrueISRCollection->setSubset( true );
	IMPL::LCCollectionVec* outputRecoISRCollection(NULL);
	outputRecoISRCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	outputRecoISRCollection->setSubset( true );
	IMPL::LCCollectionVec* outputBackgroundCollection(NULL);
	outputBackgroundCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	outputBackgroundCollection->setSubset( true );



	std::string trueJetTypeStr[6]{ "hadronic(string)" , "leptonic" , "hadronic(cluster)" , "ISR" , "overlay" , "M.E. photon" };
	std::string icnType[6]{ "quark pair" , "lepton pair" , "quark pair" , "ISR" , "???" , "M.E. photon" };
	streamlog_out(MESSAGE) << "" << std::endl;
	streamlog_out(MESSAGE) << "	////////////////////////////////////////////////////////////////////////////" << std::endl;
	streamlog_out(MESSAGE) << "	////////////////////	Processing event: 	" << pLCEvent->getEventNumber() << "	////////////////////" << std::endl;
	streamlog_out(MESSAGE) << "	////////////////////////////////////////////////////////////////////////////" << std::endl;

	try
	{
		newPfoVector IsoLeps{};
		pfoVector IsoLepsFSRs{};
		std::vector<unsigned int> IsoLepsWithFSRindex{};
		std::vector<unsigned int> IsoLepsTrueJetindex{};
		std::vector<unsigned int> IsoLepFSRsTrueJetindex{};
		//newPfoVector IsoLeptons{};
		mcpVector trueIsoLeptons{};
		mcpVector trueQuarks{};
		mcpVector trueISRPhotons{};
		pfoVector ISRPhotons{};
		pfoVector refinedPFOs{};
		pfoVector backgrounds{};
		pfoVectorVector Jets{};
		pfoVector JetsParticles{};
		newPfoVector PerfectJets{};
		std::vector<int> JetsType{};
		pfoVector goodPFOs{};
		pfoVectorVector ParticlesLists{};
		newPfoVectorVector NewParticlesLists{};
		LCRelationNavigator RecoMCParticleNav( pLCEvent->getCollection( _recoMCTruthLink ) );
		LCRelationNavigator MCParticleRecoNav( pLCEvent->getCollection( _MCTruthRecoLink ) );
		streamlog_out(DEBUG6) << "	Reading collection " << m_inputPFOCollection << std::endl;
		pfoCollection		= pLCEvent->getCollection( m_inputPFOCollection );
		int nPFOs = pfoCollection->getNumberOfElements();
		for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
			goodPFOs.push_back( pfo );
		}
		streamlog_out(DEBUG6) << "	Collection " << m_inputPFOCollection << " was red with " << nPFOs << " elements" << std::endl;
		int nIsoLeps = 0;
		if( !m_cheatIsoLepton )
		{
			streamlog_out(DEBUG6) << "	Reading collection " << m_inputIsoLepCollection << std::endl;
			isoLepCollection		= pLCEvent->getCollection( m_inputIsoLepCollection );
			nIsoLeps = isoLepCollection->getNumberOfElements();
			streamlog_out(DEBUG6) << "	Collection " << m_inputIsoLepCollection << " was red with " << nIsoLeps << " elements" << std::endl;
			for ( int i_lep = 0 ; i_lep < nIsoLeps ; ++i_lep )
			{
				ReconstructedParticleImpl* recoIsoLep = dynamic_cast<ReconstructedParticleImpl*>( isoLepCollection->getElementAt( i_lep ) );
				IsoLeps.push_back( recoIsoLep );
				streamlog_out(DEBUG1) << "A Charged lepton is found IsolatedLeptonTagging" << std::endl;
				streamlog_out(DEBUG1) << *recoIsoLep << std::endl;
			}
		}

		TrueJet_Parser* trueJet	= this;
		trueJet->getall( pLCEvent );
		streamlog_out(DEBUG6) << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;

		int njets = trueJet->njets();
		//_COUNT_FSR = 1;
		streamlog_out(DEBUG6) << "	Number of True Jets: " << njets << std::endl;
		for ( int i_trueJet = 0 ; i_trueJet < njets ; ++i_trueJet )
		{
			int trueJetType = type_jet( i_trueJet );
			int originJet = i_trueJet;
			bool jetIsFromGluonSplitting = false;
			if ( trueJetType >= 100 )
			{
				trueJetType = trueJetType % 100;
				originJet = trueJetType / 100;
				jetIsFromGluonSplitting = true;
			}
			streamlog_out(DEBUG5) << "Type of trueJet[ " << i_trueJet << " ] = " << type_jet( i_trueJet ) << std::endl;
			if ( jetIsFromGluonSplitting ) streamlog_out(DEBUG5) << " *This jet is from Gluon Splitting , origin jet index is " << originJet << std::endl;
			if ( abs( trueJetType ) != 5 )
			{
				streamlog_out(DEBUG4) << "		initial_element (Px,Py,Pz,E):	" << initial_elementon( i_trueJet )->getMomentum()[ 0 ] << " , " << initial_elementon( i_trueJet )->getMomentum()[ 1 ] << " , " << initial_elementon( i_trueJet )->getMomentum()[ 2 ] << " , " << initial_elementon( i_trueJet )->getEnergy() << std::endl;
				streamlog_out(DEBUG4) << "		final_element (Px,Py,Pz,E):	" << final_elementon( i_trueJet )->getMomentum()[ 0 ] << " , " << final_elementon( i_trueJet )->getMomentum()[ 1 ] << " , " << final_elementon( i_trueJet )->getMomentum()[ 2 ] << " , " << final_elementon( i_trueJet )->getEnergy() << std::endl;
				streamlog_out(DEBUG4) << "		Quark (Px,Py,Pz,E):		" << pquark( i_trueJet )[ 0 ] << " , " << pquark( i_trueJet )[ 1 ] << " , " << pquark( i_trueJet )[ 2 ] << " , " << Equark( i_trueJet ) << std::endl;
			}
			streamlog_out(DEBUG4) << "		trueJet (Px,Py,Pz,E):		" << ptrue( i_trueJet )[ 0 ] << " , " << ptrue( i_trueJet )[ 1 ] << " , " << ptrue( i_trueJet )[ 2 ] << " , " << Etrue( i_trueJet ) << std::endl;
			streamlog_out(DEBUG4) << "		trueOfSeenJet (Px,Py,Pz,E):	" << ptrueseen( i_trueJet )[ 0 ] << " , " << ptrueseen( i_trueJet )[ 1 ] << " , " << ptrueseen( i_trueJet )[ 2 ] << " , " << Etrueseen( i_trueJet ) << std::endl;
			streamlog_out(DEBUG4) << "		seenJet (Px,Py,Pz,E):		" << pseen( i_trueJet )[ 0 ] << " , " << pseen( i_trueJet )[ 1 ] << " , " << pseen( i_trueJet )[ 2 ] << " , " << Eseen( i_trueJet ) << std::endl;
			if ( trueJetType == 1 || trueJetType == 3 )
			{
				JetsParticles.clear();
				bool quarkExist = false;
				for ( unsigned int i = 0 ; i < trueQuarks.size() ; ++i )
				{
					if ( trueQuarks[ i ] == initial_elementon( i_trueJet ) ) quarkExist = true;
				}
				if ( !quarkExist )
				{
					trueQuarks.push_back( initial_elementon( i_trueJet ) );
					streamlog_out(DEBUG1) << "A MCParticle is found to be added to " << m_outputTrueQuarkCollection << " Collection" << std::endl;
					streamlog_out(DEBUG1) << *( initial_elementon( i_trueJet ) ) << std::endl;
				}
				JetsType.push_back( initial_elementon( i_trueJet )->getPDG() );
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					ParticlesLists.clear(); NewParticlesLists.clear();
					ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
					bool particleWasInList = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					ParticlesLists.clear();NewParticlesLists.clear();
					ParticlesLists.push_back( goodPFOs );
					bool goodPFOCandidate = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					if ( !particleWasInList && goodPFOCandidate )
					{
						refinedPFOs.push_back( seen_partics( i_trueJet )[ i_par ] );
						streamlog_out(DEBUG1) << "A Reconstructed Particle is added to " << m_outputPFOCollection << " Collection" << std::endl;
						streamlog_out(DEBUG1) << *( seen_partics( i_trueJet )[ i_par ] ) << std::endl;
						JetsParticles.push_back( seen_partics( i_trueJet )[ i_par ] );
					}
				}
				for ( unsigned int i_daughter = 0 ; i_daughter < initial_elementon( i_trueJet )->getDaughters().size() ; ++i_daughter )
				{
					MCParticle *daughter = initial_elementon( i_trueJet )->getDaughters()[ i_daughter ];
					pfoVector recoFSRPhotons{}; recoFSRPhotons.clear();
					ReconstructedParticle *FSRPhoton = NULL;
					if ( abs( daughter->getPDG() ) == 22 && daughter->getGeneratorStatus() == 1 )
					{
						float weightPFOtoMCP = 0.0;
						float weightMCPtoPFO = 0.0;
						FSRPhoton = getLinkedPFO( daughter , RecoMCParticleNav , MCParticleRecoNav , false , true , weightPFOtoMCP , weightMCPtoPFO );
						if ( FSRPhoton != NULL )
						{
							recoFSRPhotons.push_back( FSRPhoton );
						}
						else if ( daughter->getDaughters().size() > 0 )
						{
							ReconstructedParticle *recoDaughter = NULL;
							for ( unsigned int i_daughtersOfDaughters = 0 ; i_daughtersOfDaughters < daughter->getDaughters().size() ; ++i_daughtersOfDaughters )
							{
								streamlog_out(DEBUG0) << "Looking for reconstructed particle linked to daughter of true FSR photon:" << std::endl;
								streamlog_out(DEBUG0) << *( daughter->getDaughters()[ i_daughtersOfDaughters ] ) << std::endl;
								recoDaughter = getLinkedPFO( daughter->getDaughters()[ i_daughtersOfDaughters ] , RecoMCParticleNav , MCParticleRecoNav , false , false , weightPFOtoMCP , weightMCPtoPFO );
								ParticlesLists.clear(); NewParticlesLists.clear();
								ParticlesLists.push_back( recoFSRPhotons );
								bool linkedRecoParExist = checkParticleInLists( recoDaughter , ParticlesLists , NewParticlesLists );
								if ( recoDaughter != NULL && !linkedRecoParExist )
								{
									streamlog_out(DEBUG1) << "Linked reconstructed particle to daughter of true FSR photon:" << std::endl;
									streamlog_out(DEBUG1) << *recoDaughter << std::endl;
									recoFSRPhotons.push_back( recoDaughter );
								}
							}
						}
					}
					for ( unsigned int i_d = 0 ; i_d < recoFSRPhotons.size() ; ++i_d )
					{
						ParticlesLists.clear(); NewParticlesLists.clear();
						ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
						bool particleWasInList = checkParticleInLists( recoFSRPhotons[ i_d ] , ParticlesLists , NewParticlesLists );
						ParticlesLists.clear();NewParticlesLists.clear();
						ParticlesLists.push_back( goodPFOs );
						bool goodPFOCandidate = checkParticleInLists( recoFSRPhotons[ i_d ] , ParticlesLists , NewParticlesLists );
						if( !particleWasInList && goodPFOCandidate )
						{
							refinedPFOs.push_back( recoFSRPhotons[ i_d ] );
							streamlog_out(DEBUG1) << "A FSR photon is added to " << m_outputPFOCollection << " Collection" << std::endl;
							streamlog_out(DEBUG1) << *recoFSRPhotons[ i_d ] << std::endl;
							JetsParticles.push_back( recoFSRPhotons[ i_d ] );
						}
					}
				}
				Jets.push_back( JetsParticles );
			}
			else if ( trueJetType == 2 )
			{
				bool trueLeptonExist = false;
				for ( unsigned int i = 0 ; i < trueIsoLeptons.size() ; ++i )
				{
					if ( trueIsoLeptons[ i ] == initial_elementon( i_trueJet ) ) trueLeptonExist = true;
				}
				if ( !trueLeptonExist )
				{
					trueIsoLeptons.push_back( initial_elementon( i_trueJet ) );
					streamlog_out(DEBUG1) << "A MCParticle is found to be added to " << m_outputTrueIsolatedLeptonCollection << " Collection" << std::endl;
					streamlog_out(DEBUG1) << *( initial_elementon( i_trueJet ) ) << std::endl;
				}
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					ReconstructedParticleImpl* seenIsoLep = dynamic_cast<ReconstructedParticleImpl*>( seen_partics( i_trueJet )[ i_par ] );
					if ( fabs( seenIsoLep->getCharge() ) > 0.5 )
					{
						if ( m_cheatIsoLepton )
						{
							ParticlesLists.clear(); NewParticlesLists.clear();
							ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
							bool particleWasInList = checkParticleInLists( seenIsoLep , ParticlesLists , NewParticlesLists );
							ParticlesLists.clear();NewParticlesLists.clear();
							ParticlesLists.push_back( goodPFOs );
							bool goodPFOCandidate = checkParticleInLists( seenIsoLep , ParticlesLists , NewParticlesLists );
							if ( !particleWasInList && goodPFOCandidate )
							{
								IsoLeps.push_back( seenIsoLep );
								streamlog_out(DEBUG1) << "A Charged lepton in trueJet " << i_trueJet << " is found to be added to " << m_outputIsolatedLeptonCollection << " Collection" << std::endl;
								streamlog_out(DEBUG1) << *seenIsoLep << std::endl;
								IsoLepsTrueJetindex.push_back( i_trueJet );
							}
						}
					}
					else if ( seenIsoLep->getType() == 22 )
					{
						ParticlesLists.clear(); NewParticlesLists.clear();
						ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
						bool particleWasInList = checkParticleInLists( seenIsoLep , ParticlesLists , NewParticlesLists );
						ParticlesLists.clear();NewParticlesLists.clear();
						ParticlesLists.push_back( goodPFOs );
						bool goodPFOCandidate = checkParticleInLists( seenIsoLep , ParticlesLists , NewParticlesLists );
						if ( !particleWasInList && goodPFOCandidate )
						{
							IsoLepsFSRs.push_back( seenIsoLep );
							streamlog_out(DEBUG1) << "A FSR photon in trueJet " << i_trueJet << " is found to be added to " << m_outputIsolatedLeptonCollection << " Collection" << std::endl;
							streamlog_out(DEBUG1) << *seenIsoLep << std::endl;
							IsoLepFSRsTrueJetindex.push_back( i_trueJet );
						}
					}
				}
			}
			else if ( trueJetType == 4 )
			{
				for ( unsigned int i_par = 0; i_par < true_partics( i_trueJet ).size() ; ++i_par )
				{
					trueISRPhotons.push_back( true_partics( i_trueJet )[ i_par ] );
					streamlog_out(DEBUG1) << "A MCParticle is added to " << m_outputTrueISRCollection << " Collection" << std::endl;
					streamlog_out(DEBUG1) << *( true_partics( i_trueJet )[ i_par ] ) << std::endl;
				}
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					ParticlesLists.clear(); NewParticlesLists.clear();
					ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
					bool particleWasInList = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					ParticlesLists.clear();NewParticlesLists.clear();
					ParticlesLists.push_back( goodPFOs );
					bool goodPFOCandidate = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					if ( !particleWasInList && goodPFOCandidate )
					{
						ISRPhotons.push_back( seen_partics( i_trueJet )[ i_par ] );
						streamlog_out(DEBUG1) << "A Reconstructed Particle is added to " << m_outputRecoISRCollection << " Collection" << std::endl;
						streamlog_out(DEBUG1) << *( seen_partics( i_trueJet )[ i_par ] ) << std::endl;
					}
				}
			}
			else if ( trueJetType == 5 )
			{
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					ParticlesLists.clear(); NewParticlesLists.clear();
					ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
					bool particleWasInList = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					ParticlesLists.clear();NewParticlesLists.clear();
					ParticlesLists.push_back( goodPFOs );
					bool goodPFOCandidate = checkParticleInLists( seen_partics( i_trueJet )[ i_par ] , ParticlesLists , NewParticlesLists );
					if ( !particleWasInList && goodPFOCandidate )
					{
						backgrounds.push_back( seen_partics( i_trueJet )[ i_par ] );
						streamlog_out(DEBUG1) << "An Overlay Reconstructed Particle is added to " << m_outputBackgroundCollection << " Collection" << std::endl;
						streamlog_out(DEBUG1) << *( seen_partics( i_trueJet )[ i_par ] ) << std::endl;
					}
				}
			}
		}
		for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
			ParticlesLists.clear(); NewParticlesLists.clear();
			ParticlesLists.push_back( backgrounds ); ParticlesLists.push_back( ISRPhotons ); ParticlesLists.push_back( IsoLepsFSRs ); ParticlesLists.push_back( refinedPFOs ); NewParticlesLists.push_back( IsoLeps );
			bool pfoExist = checkParticleInLists( pfo , ParticlesLists , NewParticlesLists );;
			if ( !pfoExist )
			{
				backgrounds.push_back( pfo );
				if ( !m_cheatOverlay ) refinedPFOs.push_back( pfo );
			}
		}
		for ( unsigned int i_jet = 0 ; i_jet < Jets.size() ; ++i_jet )
		{
			streamlog_out(DEBUG4) << "	Forming TrueJet [ " << i_jet << " ] with " << Jets[ i_jet ].size() << " particles" << std::endl;
			ReconstructedParticleImpl* jet = new ReconstructedParticleImpl;
			TLorentzVector jetFourMomentum( 0.0 , 0.0 , 0.0 , 0.0 );
			std::vector<float> jetCovMat( 10, 0.0 );
			for ( unsigned int i_par = 0 ; i_par < Jets[ i_jet ].size() ; ++i_par )
			{
				streamlog_out(DEBUG4) << "	Adding particle [ " << i_par << " ] to TrueJet[ " << i_jet << " ]:" << std::endl;
				streamlog_out(DEBUG4) << *( Jets[ i_jet ][ i_par ] ) << std::endl;
				jetFourMomentum += TLorentzVector( Jets[ i_jet ][ i_par ]->getMomentum()[ 0 ] , Jets[ i_jet ][ i_par ]->getMomentum()[ 1 ] , Jets[ i_jet ][ i_par ]->getMomentum()[ 2 ] , Jets[ i_jet ][ i_par ]->getEnergy() );
				for ( int i_Element = 0 ; i_Element < 10 ; ++i_Element ) jetCovMat[ i_Element ] += Jets[ i_jet ][ i_par ]->getCovMatrix()[ i_Element ];
				jet->addParticle( Jets[ i_jet ][ i_par ] );
				streamlog_out(DEBUG4) << "	Particle [ " << i_par << " ] added to TrueJet[ " << i_jet << " ]:" << std::endl;
			}
			double jetMomentum[ 3 ]{ jetFourMomentum.Px() , jetFourMomentum.Py() , jetFourMomentum.Pz() };
			double jetEnergy = jetFourMomentum.E();
			jet->setMomentum( jetMomentum );
			jet->setEnergy( jetEnergy );
			jet->setCovMatrix( jetCovMat );
			jet->setMass( jetFourMomentum.M() );
			if ( JetsType.size() == Jets.size() ) jet->setType( JetsType[ i_jet ] );
			streamlog_out(DEBUG4) << "	TrueJet [ " << i_jet << " ] with " << jet->getParticles().size() << " particles is formed" << std::endl;
			streamlog_out(DEBUG4) << *( jet ) << std::endl;
			PerfectJets.push_back( jet );
		}
		for ( unsigned int i_fsr = 0 ; i_fsr < IsoLepsFSRs.size() ; ++i_fsr )
		{
			streamlog_out(DEBUG4) << "	Merging FSR [ " << i_fsr << " ] to an Isolated Lepton, FSR: " << std::endl;
			streamlog_out(DEBUG4) << *( IsoLepsFSRs[ i_fsr ] ) << std::endl;
			int i_matchedLep = -1;
			if ( m_cheatIsoLepton )
			{
				for ( unsigned int i_lep = 0 ; i_lep < IsoLeps.size() ; ++i_lep )
				{
					if ( IsoLepFSRsTrueJetindex[ i_fsr ] == IsoLepsTrueJetindex[ i_lep ] ) i_matchedLep = i_lep;
				}
			}
			else
			{
				TVector3 fsrDirection( IsoLepsFSRs[ i_fsr ]->getMomentum()[ 0 ] , IsoLepsFSRs[ i_fsr ]->getMomentum()[ 1 ] , IsoLepsFSRs[ i_fsr ]->getMomentum()[ 2 ] ); fsrDirection.SetMag( 1.0 );
				float directionMax = -1.0;
				for ( unsigned int i_lep = 0 ; i_lep < IsoLeps.size() ; ++i_lep )
				{
					TVector3 lepDirection( IsoLeps[ i_lep ]->getMomentum()[ 0 ] , IsoLeps[ i_lep ]->getMomentum()[ 1 ] , IsoLeps[ i_lep ]->getMomentum()[ 2 ] ); lepDirection.SetMag( 1.0 );
					if ( fsrDirection.Dot( lepDirection ) > directionMax )
					{
						directionMax = fsrDirection.Dot( lepDirection );
						i_matchedLep = i_lep;
					}
				}
			}
			if ( i_matchedLep != -1 && m_cheatIsoLeptonFSR )
			{
				streamlog_out(DEBUG4) << "	Merging FSR [ " << i_fsr << " ] to Isolated Lepton [ " << i_matchedLep << " ], Isolated Lepton: " << std::endl;
				streamlog_out(DEBUG4) << *( IsoLeps[ i_matchedLep ] ) << std::endl;
				IsoLepsWithFSRindex.push_back( i_matchedLep );
				double newMomentum[ 3 ]{ IsoLeps[ i_matchedLep ]->getMomentum()[ 0 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 0 ] , IsoLeps[ i_matchedLep ]->getMomentum()[ 1 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 1 ] , IsoLeps[ i_matchedLep ]->getMomentum()[ 2 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 2 ] };
				double newEnergy = IsoLeps[ i_matchedLep ]->getEnergy() + IsoLepsFSRs[ i_fsr ]->getEnergy();
				double newMass = sqrt( pow( newEnergy , 2 ) - pow( newMomentum[ 0 ] , 2 ) - pow( newMomentum[ 1 ] , 2 ) - pow( newMomentum[ 2 ] , 2 ) );
				std::vector<float> newCovMat( 10, 0.0 );
				for ( int i_element = 0 ; i_element < 10 ; ++i_element )
				{
					newCovMat[ i_element ] = IsoLeps[ i_matchedLep ]->getCovMatrix()[ i_element ] + IsoLepsFSRs[ i_fsr ]->getCovMatrix()[ i_element ];
				}
				IsoLeps[ i_matchedLep ]->setMomentum( newMomentum );
				IsoLeps[ i_matchedLep ]->setEnergy( newEnergy );
				IsoLeps[ i_matchedLep ]->setMass( newMass );
				IsoLeps[ i_matchedLep ]->setCovMatrix( newCovMat );
				IsoLeps[ i_matchedLep ]->addParticle( IsoLepsFSRs[ i_fsr ] );
				for ( unsigned int j = 0 ; j < IsoLepsFSRs[ i_fsr ]->getClusters().size() ; ++j )
				{
					IsoLeps[ i_matchedLep ]->addCluster( IsoLepsFSRs[ i_fsr ]->getClusters()[ j ] );
				}
				for ( unsigned int j = 0 ; j < IsoLepsFSRs[ i_fsr ]->getTracks().size() ; ++j)
				{
					IsoLeps[ i_matchedLep ]->addTrack( IsoLepsFSRs[ i_fsr ]->getTracks()[ j ] );
				}
				streamlog_out(DEBUG4) << "	FSR [ " << i_fsr << " ] successfully merged to Isolated Lepton [ " << i_matchedLep << " ], updated Isolated Lepton: " << std::endl;
				streamlog_out(DEBUG4) << *( IsoLeps[ i_matchedLep ] ) << std::endl;
				//IsoLeptons.push_back( IsoLeps[ i_matchedLep ] );
			}
			if ( !m_cheatIsoLeptonFSR )
			{
				bool fsrPhotonExist = false;
				for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
				{
					if ( refinedPFOs[ i ] == IsoLepsFSRs[ i_fsr ] ) fsrPhotonExist = true;
				}
				if ( !fsrPhotonExist ) refinedPFOs.push_back( IsoLepsFSRs[ i_fsr ] );
			}
		}
		if ( !m_cheatISR )
		{
			for ( unsigned int i_isr = 0 ; i_isr < ISRPhotons.size() ; ++i_isr )
			{
				bool isrPhotonExist = false;
				for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
				{
					if ( refinedPFOs[ i ] == ISRPhotons[ i_isr ] ) isrPhotonExist = true;
				}
				if ( !isrPhotonExist ) refinedPFOs.push_back( ISRPhotons[ i_isr ] );
			}
		}
		//for ( unsigned int i_par = 0 ; i_par < IsoLeps.size() ; ++i_par )
		//{
		//	bool isoLepExist = false;
		//	for ( unsigned int i_lep = 0 ; i_lep < IsoLepsWithFSRindex.size() ; ++i_lep )
		//	{
		//		if ( i_par == IsoLepsWithFSRindex[ i_lep ] ) isoLepExist = true;
		//	}
		//	if ( !isoLepExist ) IsoLeptons.push_back( IsoLeps[ i_par ] );
		//}
		streamlog_out(DEBUG7) << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		streamlog_out(DEBUG7) << "		" << trueISRPhotons.size() << " True ISR Photons are Found" << std::endl;
		streamlog_out(DEBUG7) << "		" << PerfectJets.size() << " Perfect Jets are Found" << std::endl;
		streamlog_out(DEBUG7) << "		" << trueIsoLeptons.size() << " True Isolated Leptons are Found" << std::endl;
		streamlog_out(DEBUG7) << "		" << trueQuarks.size() << " True Quarks are Found" << std::endl;
		streamlog_out(DEBUG7) << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		streamlog_out(DEBUG7) << "	" << nPFOs << " PFOs were investigated" << std::endl;
		streamlog_out(DEBUG7) << "		" << IsoLeps.size() << " PFOs as Isolated Leptons (" << ( m_cheatIsoLeptonFSR ? "with" : "without" ) << " FSR photons)" << std::endl;
		streamlog_out(DEBUG7) << "		" << IsoLepsFSRs.size() << " PFOs as FSR of Isolated Leptons (merged to " << ( m_cheatIsoLeptonFSR ? "IsolatedLeptons" : "RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG7) << "		" << ISRPhotons.size() << " PFOs as ISR Photons (" << ( m_cheatISR ? "Isolated" : "merged to RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG7) << "		" << backgrounds.size() << " PFOs as Backgrounds (" << ( m_cheatOverlay ? "Rejected" : "merged to RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG7) << "		" << refinedPFOs.size() << " PFOs as Remaining PFOs to be clustered in to recoJets" << std::endl;
		for ( unsigned int i_par = 0 ; i_par < PerfectJets.size() ; ++i_par )
		{
			outputJetCollection->addElement( PerfectJets[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < IsoLeps.size() ; ++i_par )
		{
			outputIsoLepCollection->addElement( IsoLeps[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < trueISRPhotons.size() ; ++i_par )
		{
			outputTrueISRCollection->addElement( trueISRPhotons[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < trueIsoLeptons.size() ; ++i_par )
		{
			outputTrueIsolateLeptonCollection->addElement( trueIsoLeptons[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < trueQuarks.size() ; ++i_par )
		{
			outputTrueQuarkCollection->addElement( trueQuarks[ i_par ] );
		}

		for ( unsigned int i_par = 0 ; i_par < ISRPhotons.size() ; ++i_par )
		{
			outputRecoISRCollection->addElement( ISRPhotons[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < backgrounds.size() ; ++i_par )
		{
			outputBackgroundCollection->addElement( backgrounds[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < refinedPFOs.size() ; ++i_par )
		{
			outputPfoCollection->addElement( refinedPFOs[ i_par ] );
		}

		streamlog_out(DEBUG8) << "	Output " << m_outputJetCollection << " Collection with " << outputJetCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputJetCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputJetCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG6) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputIsolatedLeptonCollection << " Collection with " << outputIsoLepCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputIsoLepCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputIsoLepCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG6) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputTrueISRCollection << " Collection with " << outputTrueISRCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_mcp = 0 ; i_mcp < outputTrueISRCollection->getNumberOfElements() ; ++i_mcp )
		{
			MCParticle *mcp = dynamic_cast<MCParticle*>( outputTrueISRCollection->getElementAt( i_mcp ) );
			streamlog_out(DEBUG6) << "		TrueParticle[ " << i_mcp << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *mcp << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputTrueIsolatedLeptonCollection << " Collection with " << outputTrueIsolateLeptonCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_mcp = 0 ; i_mcp < outputTrueIsolateLeptonCollection->getNumberOfElements() ; ++i_mcp )
		{
			MCParticle *mcp = dynamic_cast<MCParticle*>( outputTrueIsolateLeptonCollection->getElementAt( i_mcp ) );
			streamlog_out(DEBUG6) << "		TrueParticle[ " << i_mcp << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *mcp << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputTrueQuarkCollection << " Collection with " << outputTrueQuarkCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_mcp = 0 ; i_mcp < outputTrueQuarkCollection->getNumberOfElements() ; ++i_mcp )
		{
			MCParticle *mcp = dynamic_cast<MCParticle*>( outputTrueQuarkCollection->getElementAt( i_mcp ) );
			streamlog_out(DEBUG6) << "		TrueParticle[ " << i_mcp << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *mcp << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputRecoISRCollection << " Collection with " << outputRecoISRCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputRecoISRCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputRecoISRCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG6) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputPFOCollection << " Collection with " << outputPfoCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputPfoCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputPfoCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG6) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputBackgroundCollection << " Collection with " << outputBackgroundCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputBackgroundCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputBackgroundCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG6) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG6) << *pfo << std::endl;
		}

		pLCEvent->addCollection( outputJetCollection , m_outputJetCollection );
		pLCEvent->addCollection( outputIsoLepCollection , m_outputIsolatedLeptonCollection );
		pLCEvent->addCollection( outputTrueIsolateLeptonCollection , m_outputTrueIsolatedLeptonCollection );
		pLCEvent->addCollection( outputTrueQuarkCollection , m_outputTrueQuarkCollection );
		pLCEvent->addCollection( outputTrueISRCollection , m_outputTrueISRCollection );
		pLCEvent->addCollection( outputRecoISRCollection , m_outputRecoISRCollection );
		pLCEvent->addCollection( outputBackgroundCollection , m_outputBackgroundCollection );
		pLCEvent->addCollection( outputPfoCollection , m_outputPFOCollection );

	}
	catch(DataNotAvailableException &e)
	{
		streamlog_out(MESSAGE) << "	Check : Input collections not found in event " << pLCEvent->getEventNumber() << std::endl;
	}


}

EVENT::ReconstructedParticle* TrueJetIsoLepISRBG::getLinkedPFO( EVENT::MCParticle *mcParticle , LCRelationNavigator RecoMCParticleNav , LCRelationNavigator MCParticleRecoNav , bool getChargedPFO , bool getNeutralPFO , float &weightPFOtoMCP , float &weightMCPtoPFO )
{
	streamlog_out(DEBUG1) << "" << std::endl;
	streamlog_out(DEBUG1) << "Look for PFO linked to visible MCParticle:" << std::endl;

	ReconstructedParticle* linkedPFO{};
	bool foundlinkedPFO = false;
	const EVENT::LCObjectVec& PFOvec = MCParticleRecoNav.getRelatedToObjects( mcParticle );
	const EVENT::FloatVec&	PFOweightvec = MCParticleRecoNav.getRelatedToWeights( mcParticle );
	streamlog_out(DEBUG0) << "Visible MCParticle is linked to " << PFOvec.size() << " PFO(s)" << std::endl;
	weightPFOtoMCP = 0.0;
	weightMCPtoPFO = 0.0;
	double maxweightPFOtoMCP = 0.;
	double maxweightMCPtoPFO = 0.;
	int iPFOtoMCPmax = -1;
	int iMCPtoPFOmax = -1;
	for ( unsigned int i_pfo = 0; i_pfo < PFOvec.size(); i_pfo++ )
	{
		double pfo_weight = 0.0;
		double trackWeight = ( int( PFOweightvec.at( i_pfo ) ) % 10000 ) / 1000.0;
		double clusterWeight = ( int( PFOweightvec.at( i_pfo ) ) / 10000 ) / 1000.0;
		if ( getChargedPFO && !getNeutralPFO )
		{
			pfo_weight = trackWeight;
		}
		else if ( getNeutralPFO && !getChargedPFO )
		{
			pfo_weight = clusterWeight;
		}
		else
		{
			pfo_weight = ( trackWeight > clusterWeight ? trackWeight : clusterWeight );
		}
		streamlog_out(DEBUG0) << "Visible MCParticle linkWeight to PFO: " << PFOweightvec.at( i_pfo ) << " (Track: " << trackWeight << " , Cluster: " << clusterWeight << ")" << std::endl;
		ReconstructedParticle *testPFO = (ReconstructedParticle *) PFOvec.at( i_pfo );
		if ( pfo_weight > maxweightMCPtoPFO )//&& track_weight >= m_MinWeightTrackMCTruthLink )
		{
			maxweightMCPtoPFO = pfo_weight;
			iMCPtoPFOmax = i_pfo;
			streamlog_out(DEBUG0) << "PFO at index: " << testPFO->id() << " has TYPE: " << testPFO->getType() << " and MCParticle to PFO link weight is " << pfo_weight << std::endl;
		}
	}
	if ( getChargedPFO && maxweightMCPtoPFO < 0.8 )
	{
		streamlog_out(DEBUG1) << "MCParticle has link weight lower than 0.8 ( " << maxweightMCPtoPFO << " ), looking for linked PFO in clusters" << std::endl;
		for ( unsigned int i_pfo = 0; i_pfo < PFOvec.size(); i_pfo++ )
		{
			double pfo_weight = ( int( PFOweightvec.at( i_pfo ) ) / 10000 ) / 1000.0;
			streamlog_out(DEBUG0) << "Visible MCParticle linkWeight to PFO: " << PFOweightvec.at( i_pfo ) << " (Track: " << ( int( PFOweightvec.at( i_pfo ) ) % 10000 ) / 1000.0 << " , Cluster: " << ( int( PFOweightvec.at( i_pfo ) ) / 10000 ) / 1000.0 << ")" << std::endl;
			ReconstructedParticle *testPFO = (ReconstructedParticle *) PFOvec.at( i_pfo );
			if ( pfo_weight > maxweightMCPtoPFO )//&& track_weight >= m_MinWeightTrackMCTruthLink )
			{
				maxweightMCPtoPFO = pfo_weight;
				iMCPtoPFOmax = i_pfo;
				streamlog_out(DEBUG0) << "PFO at index: " << testPFO->id() << " has TYPE: " << testPFO->getType() << " and MCParticle to PFO link weight is " << pfo_weight << std::endl;
			}
		}
	}
	if ( iMCPtoPFOmax != -1 )
	{
		ReconstructedParticle *testPFO = (ReconstructedParticle *) PFOvec.at( iMCPtoPFOmax );
		const EVENT::LCObjectVec& MCPvec = RecoMCParticleNav.getRelatedToObjects( testPFO );
		const EVENT::FloatVec&	MCPweightvec = RecoMCParticleNav.getRelatedToWeights( testPFO );
		for ( unsigned int i_mcp = 0; i_mcp < MCPvec.size(); i_mcp++ )
		{
			double mcp_weight = 0.0;
			double trackWeight = ( int( MCPweightvec.at( i_mcp ) ) % 10000 ) / 1000.0;
			double clusterWeight = ( int( MCPweightvec.at( i_mcp ) ) / 10000 ) / 1000.0;
			if ( getChargedPFO && !getNeutralPFO )
			{
				mcp_weight = trackWeight;
			}
			else if ( getNeutralPFO && !getChargedPFO )
			{
				mcp_weight = clusterWeight;
			}
			else
			{
				mcp_weight = ( trackWeight > clusterWeight ? trackWeight : clusterWeight );
			}
			MCParticle *testMCP = (MCParticle *) MCPvec.at( i_mcp );
			if ( mcp_weight > maxweightPFOtoMCP )//&& mcp_weight >= m_MinWeightTrackMCTruthLink )
			{
				maxweightPFOtoMCP = mcp_weight;
				iPFOtoMCPmax = i_mcp;
				streamlog_out(DEBUG0) << "MCParticle at index: " << testMCP->id() << " has PDG: " << testMCP->getPDG() << " and PFO to MCParticle link weight is " << mcp_weight << std::endl;
			}
		}
		if ( iPFOtoMCPmax != -1 )
		{
			if ( MCPvec.at( iPFOtoMCPmax ) == mcParticle )
			{
				linkedPFO = testPFO;
				foundlinkedPFO = true;
			}
		}
	}
	if( foundlinkedPFO )
	{
		streamlog_out(DEBUG1) << "Linked PFO to MCParticle found successfully " << std::endl;
		weightPFOtoMCP = maxweightPFOtoMCP;
		weightMCPtoPFO = maxweightMCPtoPFO;
		return linkedPFO;
	}
	else
	{
		streamlog_out(DEBUG1) << "Couldn't Find a PFO linked to MCParticle" << std::endl;
		return NULL;
	}
}

bool TrueJetIsoLepISRBG::checkParticleInLists( EVENT::ReconstructedParticle* pfo , pfoVectorVector ParticleLists , newPfoVectorVector NewParticleLists )
{
	bool particleIsInList = false;
	for ( unsigned int i_List = 0 ; i_List < ParticleLists.size() ; ++i_List )
	{
		for ( unsigned int i_Par = 0 ; i_Par < ParticleLists[ i_List ].size() ; ++i_Par )
		{
			if ( pfo == ParticleLists[ i_List ][ i_Par ] ) particleIsInList = true;
		}
	}
	for ( unsigned int i_List = 0 ; i_List < NewParticleLists.size() ; ++i_List )
	{
		for ( unsigned int i_Par = 0 ; i_Par < NewParticleLists[ i_List ].size() ; ++i_Par )
		{
			if ( pfo == NewParticleLists[ i_List ][ i_Par ] ) particleIsInList = true;
		}
	}
	return particleIsInList;
}

bool TrueJetIsoLepISRBG::checkParticleInLists( ReconstructedParticleImpl* pfo , pfoVectorVector ParticleLists , newPfoVectorVector NewParticleLists )
{
	bool particleIsInList = false;
	for ( unsigned int i_List = 0 ; i_List < ParticleLists.size() ; ++i_List )
	{
		for ( unsigned int i_Par = 0 ; i_Par < ParticleLists[ i_List ].size() ; ++i_Par )
		{
			if ( pfo == ParticleLists[ i_List ][ i_Par ] ) particleIsInList = true;
		}
	}
	for ( unsigned int i_List = 0 ; i_List < NewParticleLists.size() ; ++i_List )
	{
		for ( unsigned int i_Par = 0 ; i_Par < NewParticleLists[ i_List ].size() ; ++i_Par )
		{
			if ( pfo == NewParticleLists[ i_List ][ i_Par ] ) particleIsInList = true;
		}
	}
	return particleIsInList;
}

void TrueJetIsoLepISRBG::check( LCEvent *pLCEvent )
{
	LCCollection *outputJetCollection{};
	LCCollection *outputIsoLepCollection{};
	LCCollection *outputTrueISRCollection{};
	LCCollection *outputTrueIsolateLeptonCollection{};
	LCCollection *outputTrueQuarkCollection{};
	LCCollection *outputRecoISRCollection{};
	LCCollection *outputBackgroundCollection{};
	LCCollection *outputPfoCollection{};
	try
	{
		outputJetCollection = pLCEvent->getCollection( m_outputJetCollection );
		outputIsoLepCollection = pLCEvent->getCollection( m_outputIsolatedLeptonCollection );
		outputTrueIsolateLeptonCollection = pLCEvent->getCollection( m_outputTrueIsolatedLeptonCollection );
		outputTrueISRCollection = pLCEvent->getCollection( m_outputTrueISRCollection );
		outputTrueQuarkCollection = pLCEvent->getCollection( m_outputTrueQuarkCollection );
		outputRecoISRCollection = pLCEvent->getCollection( m_outputRecoISRCollection );
		outputBackgroundCollection = pLCEvent->getCollection( m_outputBackgroundCollection );
		outputPfoCollection = pLCEvent->getCollection( m_outputPFOCollection );
		int n_outputJets = outputJetCollection->getNumberOfElements();
		int n_outputIsoLeps = outputIsoLepCollection->getNumberOfElements();
		int n_outputTrueIsoLeps = outputTrueIsolateLeptonCollection->getNumberOfElements();
		int n_outputTrueISRs = outputTrueISRCollection->getNumberOfElements();
		int n_outputTrueQuarks = outputTrueQuarkCollection->getNumberOfElements();
		int n_outputRecoISRs = outputRecoISRCollection->getNumberOfElements();
		int n_outputBGs = outputBackgroundCollection->getNumberOfElements();
		int n_outputPFOs = outputPfoCollection->getNumberOfElements();
		streamlog_out(DEBUG9) << "	CHECK : processed event: " << pLCEvent->getEventNumber() << " (Number of outputJets: " << n_outputJets << " , Number of outputIsoLeps: True: " << n_outputTrueIsoLeps << " and Reco: " << n_outputIsoLeps << " , Number of outputISRs: True: " << n_outputTrueISRs << " and Reco: " << n_outputRecoISRs << " , Number of Quarks: " << n_outputTrueQuarks << " , Number of outputPFOs: " << n_outputPFOs << " , Number of outputBGs: " << n_outputBGs << ")" << std::endl;
	}
	catch(DataNotAvailableException &e)
        {
          streamlog_out(MESSAGE) << "	Input/Output collection not found in event " << pLCEvent->getEventNumber() << std::endl;
        }

}

void TrueJetIsoLepISRBG::end()
{

}
