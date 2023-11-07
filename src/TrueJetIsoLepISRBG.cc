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
								"outputIsolatedLeptonCollection" ,
								"Name of the output Isolated Lepton collection"  ,
								m_outputIsolatedLeptonCollection ,
								std::string("trueIsolatedLeptons")
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
	IMPL::LCCollectionVec* outputIsoLepCollection(NULL);
	outputIsoLepCollection = new IMPL::LCCollectionVec( LCIO::RECONSTRUCTEDPARTICLE );
	outputIsoLepCollection->setSubset( true );
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
		//newPfoVector IsoLeptons{};
		mcpVector trueISRPhotons{};
		pfoVector ISRPhotons{};
		pfoVector refinedPFOs{};
		pfoVector backgrounds{};
		LCRelationNavigator RecoMCParticleNav( pLCEvent->getCollection( _recoMCTruthLink ) );
		LCRelationNavigator MCParticleRecoNav( pLCEvent->getCollection( _MCTruthRecoLink ) );
		streamlog_out(DEBUG6) << "	Reading collection " << m_inputPFOCollection << std::endl;
		pfoCollection		= pLCEvent->getCollection( m_inputPFOCollection );
		int nPFOs = pfoCollection->getNumberOfElements();
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
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					bool particleWasInList = false;
					for ( unsigned int i = 0 ; i < backgrounds.size() ; ++i )
					{
						if ( backgrounds[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < ISRPhotons.size() ; ++i )
					{
						if ( ISRPhotons[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLepsFSRs.size() ; ++i )
					{
						if ( IsoLepsFSRs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
					{
						if ( IsoLeps[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
					{
						if ( refinedPFOs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					bool goodPFOCandidate = false;
					for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
					{
						ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
						if ( seen_partics( i_trueJet )[ i_par ] == pfo ) goodPFOCandidate = true;
					}
					if ( !particleWasInList && goodPFOCandidate )
					{
						refinedPFOs.push_back( seen_partics( i_trueJet )[ i_par ] );
						streamlog_out(DEBUG1) << "A Reconstructed Particle is added to " << m_outputPFOCollection << " Collection" << std::endl;
						streamlog_out(DEBUG1) << *( seen_partics( i_trueJet )[ i_par ] ) << std::endl;
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
								bool linkedRecoParExist = false;
								for ( unsigned int i_recoPar = 0 ; i_recoPar < recoFSRPhotons.size() ; ++i_recoPar )
								{
									if ( recoFSRPhotons[ i_recoPar ] == recoDaughter ) linkedRecoParExist = true;
								}
								if ( recoDaughter != NULL && !linkedRecoParExist )
								{
									streamlog_out(DEBUG1) << "Linked reconstructed particle to daughter of true FSR photon:" << std::endl;
									streamlog_out(DEBUG1) << *recoDaughter << std::endl;
									recoFSRPhotons.push_back( recoDaughter );
								}
							}
						}
						for ( unsigned int i_d = 0 ; i_d < recoFSRPhotons.size() ; ++i_d )
						{
							bool linkedRecoParExist = false;
							for ( unsigned int i = 0 ; i < backgrounds.size() ; ++i )
							{
								if ( backgrounds[ i ] == recoFSRPhotons[ i_d ] ) linkedRecoParExist = true;
							}
							for ( unsigned int i = 0 ; i < ISRPhotons.size() ; ++i )
							{
								if ( ISRPhotons[ i ] == recoFSRPhotons[ i_d ] ) linkedRecoParExist = true;
							}
							for ( unsigned int i = 0 ; i < IsoLepsFSRs.size() ; ++i )
							{
								if ( IsoLepsFSRs[ i ] == recoFSRPhotons[ i_d ] ) linkedRecoParExist = true;
							}
							for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
							{
								if ( IsoLeps[ i ] == recoFSRPhotons[ i_d ] ) linkedRecoParExist = true;
							}
							for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
							{
								if ( refinedPFOs[ i ] == recoFSRPhotons[ i_d ] ) linkedRecoParExist = true;
							}
							bool goodPFOCandidate = false;
							for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
							{
								ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
								if ( recoFSRPhotons[ i_d ] == pfo ) goodPFOCandidate = true;
							}
							if( !linkedRecoParExist && goodPFOCandidate )
							{
								refinedPFOs.push_back( recoFSRPhotons[ i_d ] );
								streamlog_out(DEBUG1) << "A FSR photon is added to " << m_outputPFOCollection << " Collection" << std::endl;
								streamlog_out(DEBUG1) << *recoFSRPhotons[ i_d ] << std::endl;
							}
						}
					}
				}
			}
			else if ( trueJetType == 2 )
			{
				for ( unsigned int i_par = 0; i_par < seen_partics( i_trueJet ).size() ; ++i_par )
				{
					ReconstructedParticleImpl* seenIsoLep = dynamic_cast<ReconstructedParticleImpl*>( seen_partics( i_trueJet )[ i_par ] );
					if ( seenIsoLep->getTracks().size() == 1 )
					{
						if ( m_cheatIsoLepton )
						{
							bool particleWasInList = false;
							for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
							{
								if ( IsoLeps[ i ] == seenIsoLep ) particleWasInList = true;
							}
							if ( !particleWasInList )
							{
								IsoLeps.push_back( seenIsoLep );
								streamlog_out(DEBUG1) << "A Charged lepton is found to be added to " << m_outputIsolatedLeptonCollection << " Collection" << std::endl;
								streamlog_out(DEBUG1) << *seenIsoLep << std::endl;
							}
						}
					}
					else
					{
						bool particleWasInList = false;
						for ( unsigned int i = 0 ; i < backgrounds.size() ; ++i )
						{
							if ( backgrounds[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
						}
						for ( unsigned int i = 0 ; i < ISRPhotons.size() ; ++i )
						{
							if ( ISRPhotons[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
						}
						for ( unsigned int i = 0 ; i < IsoLepsFSRs.size() ; ++i )
						{
							if ( IsoLepsFSRs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
						}
						for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
						{
							if ( IsoLeps[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
						}
						for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
						{
							if ( refinedPFOs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
						}
						bool goodPFOCandidate = false;
						for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
						{
							ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
							if ( seen_partics( i_trueJet )[ i_par ] == pfo ) goodPFOCandidate = true;
						}
						if ( !particleWasInList && goodPFOCandidate )
						{
							IsoLepsFSRs.push_back( seenIsoLep );
							streamlog_out(DEBUG1) << "A FSR photon is found to be added to " << m_outputIsolatedLeptonCollection << " Collection" << std::endl;
							streamlog_out(DEBUG1) << *seenIsoLep << std::endl;
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
					bool particleWasInList = false;
					for ( unsigned int i = 0 ; i < ISRPhotons.size() ; ++i )
					{
						if ( ISRPhotons[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLepsFSRs.size() ; ++i )
					{
						if ( IsoLepsFSRs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
					{
						if ( IsoLeps[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
					{
						if ( refinedPFOs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < backgrounds.size() ; ++i )
					{
						if ( backgrounds[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					bool goodPFOCandidate = false;
					for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
					{
						ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
						if ( seen_partics( i_trueJet )[ i_par ] == pfo ) goodPFOCandidate = true;
					}
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
					bool particleWasInList = false;
					for ( unsigned int i = 0 ; i < backgrounds.size() ; ++i )
					{
						if ( backgrounds[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < ISRPhotons.size() ; ++i )
					{
						if ( ISRPhotons[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLepsFSRs.size() ; ++i )
					{
						if ( IsoLepsFSRs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < IsoLeps.size() ; ++i )
					{
						if ( IsoLeps[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					for ( unsigned int i = 0 ; i < refinedPFOs.size() ; ++i )
					{
						if ( refinedPFOs[ i ] == seen_partics( i_trueJet )[ i_par ] ) particleWasInList = true;
					}
					bool goodPFOCandidate = false;
					for ( int i_pfo = 0 ; i_pfo < nPFOs ; ++i_pfo )
					{
						ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( pfoCollection->getElementAt( i_pfo ) );
						if ( seen_partics( i_trueJet )[ i_par ] == pfo ) goodPFOCandidate = true;
					}
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
			bool pfoExist = false;
			for ( unsigned int i_par = 0 ; i_par < refinedPFOs.size() ; ++i_par )
			{
				if ( refinedPFOs[ i_par ] == pfo ) pfoExist = true;
			}
			for ( unsigned int i_par = 0 ; i_par < IsoLeps.size() ; ++i_par )
			{
				if ( IsoLeps[ i_par ] == pfo ) pfoExist = true;
			}
			for ( unsigned int i_par = 0 ; i_par < IsoLepsFSRs.size() ; ++i_par )
			{
				if ( IsoLepsFSRs[ i_par ] == pfo ) pfoExist = true;
			}
			for ( unsigned int i_par = 0 ; i_par < ISRPhotons.size() ; ++i_par )
			{
				if ( ISRPhotons[ i_par ] == pfo ) pfoExist = true;
			}
			if ( !pfoExist )
			{
				backgrounds.push_back( pfo );
				if ( !m_cheatOverlay ) refinedPFOs.push_back( pfo );
			}
		}
		for ( unsigned int i_fsr = 0 ; i_fsr < IsoLepsFSRs.size() ; ++i_fsr )
		{
			TVector3 fsrDirection( IsoLepsFSRs[ i_fsr ]->getMomentum() ); fsrDirection.SetMag( 1.0 );
			double cosMaxAngle = -1.0;
			int i_matchedLep = -1;
			for ( unsigned int i_lep = 0 ; i_lep < IsoLeps.size() ; ++i_lep )
			{
				TVector3 lepDirection( IsoLeps[ i_lep ]->getMomentum() ); lepDirection.SetMag( 1.0 );
				if ( lepDirection.Dot( fsrDirection ) > cosMaxAngle )
				{
					cosMaxAngle = lepDirection.Dot( fsrDirection );
					i_matchedLep = i_lep;
				}
			}
			if ( i_matchedLep != -1 && m_cheatIsoLeptonFSR )
			{
				IsoLepsWithFSRindex.push_back( i_matchedLep );
				double newMomentum[ 3 ]{ IsoLeps[ i_matchedLep ]->getMomentum()[ 0 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 0 ] , IsoLeps[ i_matchedLep ]->getMomentum()[ 1 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 1 ] , IsoLeps[ i_matchedLep ]->getMomentum()[ 2 ] + IsoLepsFSRs[ i_fsr ]->getMomentum()[ 2 ] };
				double newEnergy = IsoLeps[ i_matchedLep ]->getEnergy() + IsoLepsFSRs[ i_fsr ]->getEnergy();
				std::vector<float> newCovMat( 10, 0.0 );
				for ( int i_element = 0 ; i_element < 10 ; ++i_element )
				{
					newCovMat[ i_element ] = IsoLeps[ i_matchedLep ]->getCovMatrix()[ i_element ] + IsoLepsFSRs[ i_fsr ]->getCovMatrix()[ i_element ];
				}
				IsoLeps[ i_matchedLep ]->setMomentum( newMomentum );
				IsoLeps[ i_matchedLep ]->setEnergy( newEnergy );
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
		streamlog_out(DEBUG6) << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
		streamlog_out(DEBUG6) << "	" << nPFOs << " PFOs were investigated" << std::endl;
		streamlog_out(DEBUG6) << "		" << IsoLeps.size() << " PFOs as Isolated Leptons (" << ( m_cheatIsoLeptonFSR ? "with" : "without" ) << " FSR photons)" << std::endl;
		streamlog_out(DEBUG6) << "		" << IsoLepsFSRs.size() << " PFOs as FSR of Isolated Leptons (merged to" << ( m_cheatIsoLeptonFSR ? "IsolatedLeptons" : "RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG6) << "		" << ISRPhotons.size() << " PFOs as ISR Photons (" << ( m_cheatISR ? "Isolated" : "merged to RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG6) << "		" << backgrounds.size() << " PFOs as Backgrounds (" << ( m_cheatOverlay ? "Rejected" : "merged to RefinedPFOs" ) << ")" << std::endl;
		streamlog_out(DEBUG6) << "		" << refinedPFOs.size() << " PFOs as Remaining PFOs to be clustered in to recoJets" << std::endl;
		for ( unsigned int i_par = 0 ; i_par < IsoLeps.size() ; ++i_par )
		{
			outputIsoLepCollection->addElement( IsoLeps[ i_par ] );
		}
		for ( unsigned int i_par = 0 ; i_par < trueISRPhotons.size() ; ++i_par )
		{
			outputTrueISRCollection->addElement( trueISRPhotons[ i_par ] );
		}

		for ( unsigned int i_par = 0 ; i_par < ISRPhotons.size() ; ++i_par )
		{
			if ( m_cheatISR )
			{
				outputRecoISRCollection->addElement( ISRPhotons[ i_par ] );
			}
			else
			{
				outputPfoCollection->addElement( ISRPhotons[ i_par ] );
			}
		}
		for ( unsigned int i_par = 0 ; i_par < backgrounds.size() ; ++i_par )
		{
			if ( m_cheatOverlay )
			{
				outputBackgroundCollection->addElement( backgrounds[ i_par ] );
			}
			else
			{
				outputPfoCollection->addElement( backgrounds[ i_par ] );
			}
		}
		for ( unsigned int i_par = 0 ; i_par < refinedPFOs.size() ; ++i_par )
		{
			outputPfoCollection->addElement( refinedPFOs[ i_par ] );
		}

		streamlog_out(DEBUG8) << "	Output " << m_outputIsolatedLeptonCollection << " Collection with " << outputIsoLepCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputIsoLepCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputIsoLepCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG3) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG3) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputTrueISRCollection << " Collection with " << outputTrueISRCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_mcp = 0 ; i_mcp < outputTrueISRCollection->getNumberOfElements() ; ++i_mcp )
		{
			MCParticle *mcp = dynamic_cast<MCParticle*>( outputTrueISRCollection->getElementAt( i_mcp ) );
			streamlog_out(DEBUG3) << "		TrueParticle[ " << i_mcp << " ]:" << std::endl;
			streamlog_out(DEBUG3) << *mcp << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputRecoISRCollection << " Collection with " << outputRecoISRCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputRecoISRCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputRecoISRCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG3) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG3) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputPFOCollection << " Collection with " << outputPfoCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputPfoCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputPfoCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG3) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG3) << *pfo << std::endl;
		}
		streamlog_out(DEBUG8) << "	Output " << m_outputBackgroundCollection << " Collection with " << outputBackgroundCollection->getNumberOfElements() << " elements:" << std::endl;
		for ( int i_pfo = 0 ; i_pfo < outputBackgroundCollection->getNumberOfElements() ; ++i_pfo )
		{
			ReconstructedParticle *pfo = dynamic_cast<ReconstructedParticle*>( outputBackgroundCollection->getElementAt( i_pfo ) );
			streamlog_out(DEBUG3) << "		RecoParticle[ " << i_pfo << " ]:" << std::endl;
			streamlog_out(DEBUG3) << *pfo << std::endl;
		}

		pLCEvent->addCollection( outputIsoLepCollection , m_outputIsolatedLeptonCollection );
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

void TrueJetIsoLepISRBG::check( LCEvent *pLCEvent )
{
	LCCollection *outputIsoLepCollection{};
	LCCollection *outputTrueISRCollection{};
	LCCollection *outputRecoISRCollection{};
	LCCollection *outputBackgroundCollection{};
	LCCollection *outputPfoCollection{};
	try
	{
		outputIsoLepCollection = pLCEvent->getCollection( m_outputIsolatedLeptonCollection );
		outputTrueISRCollection = pLCEvent->getCollection( m_outputTrueISRCollection );
		outputRecoISRCollection = pLCEvent->getCollection( m_outputRecoISRCollection );
		outputBackgroundCollection = pLCEvent->getCollection( m_outputBackgroundCollection );
		outputPfoCollection = pLCEvent->getCollection( m_outputPFOCollection );
		int n_outputIsoLeps = outputIsoLepCollection->getNumberOfElements();
		int n_outputTrueISRs = outputTrueISRCollection->getNumberOfElements();
		int n_outputRecoISRs = outputRecoISRCollection->getNumberOfElements();
		int n_outputBGs = outputBackgroundCollection->getNumberOfElements();
		int n_outputPFOs = outputPfoCollection->getNumberOfElements();
		streamlog_out(DEBUG9) << "	CHECK : processed event: " << pLCEvent->getEventNumber() << " (Number of outputIsoLeps: " << n_outputIsoLeps << " , Number of outputISRs: True: " << n_outputTrueISRs << " and Reco: " << n_outputRecoISRs << " , Number of outputPFOs: " << n_outputPFOs << " , Number of outputBGs: " << n_outputBGs << ")" << std::endl;
	}
	catch(DataNotAvailableException &e)
        {
          streamlog_out(MESSAGE) << "	Input/Output collection not found in event " << pLCEvent->getEventNumber() << std::endl;
        }

}

void TrueJetIsoLepISRBG::end()
{

}
