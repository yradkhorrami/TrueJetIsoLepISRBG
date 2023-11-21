#ifndef TrueJetIsoLepISRBG_h
#define TrueJetIsoLepISRBG_h 1

#include "marlin/Processor.h"
#include "lcio.h"
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/LCRelation.h>
#include <UTIL/LCRelationNavigator.h>
#include "IMPL/LCCollectionVec.h"
#include <IMPL/ReconstructedParticleImpl.h>
#include <IMPL/ParticleIDImpl.h>
#include "DDMarlinCED.h"
#include <iostream>
#include <string>
#include "TrueJet_Parser.h"
#include "marlin/VerbosityLevels.h"
#include "TLorentzVector.h"
#include "TVector3.h"

using namespace lcio ;
using namespace marlin ;

class TrueJetIsoLepISRBG : public Processor , public TrueJet_Parser
{

	public:

		virtual Processor*  newProcessor()
		{
			return new TrueJetIsoLepISRBG;
		}

		TrueJetIsoLepISRBG();
		virtual ~TrueJetIsoLepISRBG() = default;
		TrueJetIsoLepISRBG(const TrueJetIsoLepISRBG&) = delete;
		TrueJetIsoLepISRBG& operator=(const TrueJetIsoLepISRBG&) = delete;

		typedef std::vector<EVENT::MCParticle*>					mcpVector;
		typedef std::vector<EVENT::ReconstructedParticle*>			pfoVector;
		typedef std::vector<std::vector<EVENT::ReconstructedParticle*>>		pfoVectorVector;
		typedef std::vector<ReconstructedParticleImpl*>				newPfoVector;
		typedef std::vector<std::vector<ReconstructedParticleImpl*>>		newPfoVectorVector;

		virtual void init();
		virtual void processRunHeader();
		virtual void processEvent( LCEvent * event );
		EVENT::ReconstructedParticle* getLinkedPFO( EVENT::MCParticle *mcParticle , LCRelationNavigator RecoMCParticleNav , LCRelationNavigator MCParticleRecoNav , bool getChargedPFO , bool getNeutralPFO , float &weightPFOtoMCP , float &weightMCPtoPFO );
		bool checkParticleInLists( EVENT::ReconstructedParticle* pfo , pfoVectorVector ParticleLists , newPfoVectorVector NewParticleLists );
		bool checkParticleInLists( ReconstructedParticleImpl* pfo , pfoVectorVector ParticleLists , newPfoVectorVector NewParticleLists );
		virtual void check( LCEvent * event );
		virtual void end();

		std::string get_recoMCTruthLink()
		{
			return _recoMCTruthLink;
		};

	private:

		std::string				m_inputPFOCollection{};
		std::string				m_inputIsoLepCollection{};
		std::string				m_outputJetCollection{};
		std::string				m_outputIsolatedLeptonCollection{};
		std::string				m_outputTrueIsolatedLeptonCollection{};
		std::string				m_outputTrueQuarkCollection{};
		std::string				m_outputTrueISRCollection{};
		std::string				m_outputRecoISRCollection{};
		std::string				m_outputPFOCollection{};
		std::string				m_outputBackgroundCollection{};
		std::string				_MCParticleColllectionName{};
		std::string				_recoParticleCollectionName{};
		std::string				_recoMCTruthLink{};
		std::string				_MCTruthRecoLink{};
		bool					m_cheatIsoLepton = true;
		bool					m_cheatIsoLeptonFSR = true;
		bool					m_cheatISR = true;
		bool					m_cheatOverlay = true;

};

#endif
