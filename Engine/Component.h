#pragma once

class Object;

class Component
{
public:
	
	Component() = default;
	virtual ~Component();
	//the object with wich is associated
	Object* myObject = nullptr;

	//calls to verify if component can be created
    virtual bool Init() { return true; }

	//virtual beginplay method
	virtual void Construct() {}
	//virtual start method
	virtual void Start() {}
	//virtual update method
	virtual void Update() {}
	//virtual fixupdate method
	virtual void FixUpdate() {}

};

