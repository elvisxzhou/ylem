#ifndef __FREECAMERA_H__
#define __FREECAMERA_H__

class FreeCamera : public ElvCore::Component , public ElvCore::InputCallback
{
public:
	FreeCamera();
	~FreeCamera();

	bool update(float timestep);

	void setMoveSpeed(float s)		{ mMoveSpeed   = s; }
	void setRotateSpeed(float s)	{ mRotateSpeed = s; }
	Ogre::Camera* getCamera() const { return mCamera; }
    void onAttach(void);
	bool mouseMoved(const OIS::MouseEvent & arg);

private:
	std::string getType() { return "FreeCamera"; }

private:
	Ogre::Camera*	 mCamera;
	Ogre::SceneNode* mSceneNode;
	float			 mMoveSpeed;
	float			 mRotateSpeed;

	friend class boost::serialization::access;

	template<class Archive>
	void save(Archive & ar_, const unsigned int version_) const
	{
		ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);

		ar_ & BOOST_SERIALIZATION_NVP(mMoveSpeed);
		ar_ & BOOST_SERIALIZATION_NVP(mRotateSpeed);

		const Ogre::Vector3& pos = mCamera->getPosition();//mCamera->getPosition() - mCamera->getOrientation() * Ogre::Vector3::UNIT_Z);
		const Ogre::Quaternion& quat = mCamera->getOrientation();

		ar_ & BOOST_SERIALIZATION_NVP(Ogre::StringConverter::toString(pos));
		ar_ & BOOST_SERIALIZATION_NVP(Ogre::StringConverter::toString(quat));
	}

	template<class Archive>
	void load(Archive & ar_, const unsigned int version_)
	{
		ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);

		ar_ & BOOST_SERIALIZATION_NVP(mMoveSpeed);
		ar_ & BOOST_SERIALIZATION_NVP(mRotateSpeed);

		Ogre::String str;
		ar_ & BOOST_SERIALIZATION_NVP(str);
		const Ogre::Vector3 pos = Ogre::StringConverter::parseVector3(str);
		ar_ & BOOST_SERIALIZATION_NVP(str);
		const Ogre::Quaternion quat = Ogre::StringConverter::parseQuaternion(str);

		mCamera->setPosition(pos);
		mCamera->setOrientation(quat);
	}    

	BOOST_SERIALIZATION_SPLIT_MEMBER()
};

BOOST_CLASS_EXPORT_GUID(FreeCamera, "FreeCamera")

#endif