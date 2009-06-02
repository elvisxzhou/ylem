#ifndef EG_FSM_H
#define EG_FSM_H

#include "ElvCore.h"

namespace ElvGame
{
	class FSM : public ElvCore::Component
	{
	public:
		FSM();
		~FSM();

		bool update(float timestep);

		void changeState(std::string fsm,std::string state);

	private:
		std::string getType() { return "FSM"; }
			
	private:
		typedef std::map<std::string ,std::string > FsmMap;
		FsmMap mFSMs;

		friend class boost::serialization::access;

		template<class Archive>
		void save(Archive & ar_, const unsigned int version_) const
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);
	//		ar_ & BOOST_SERIALIZATION_NVP(mFSMs);
		}

		template<class Archive>
		void load(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);
	//		ar_ & BOOST_SERIALIZATION_NVP(mFSMs);
		}    

		BOOST_SERIALIZATION_SPLIT_MEMBER()
	};

	BOOST_CLASS_EXPORT_GUID(FSM, "ElvGameFSM")

}
#endif