# Reflection
Run time reflection library for c++17

Documentation:

to use the library in a class 

you have to add the REFLECT_CLASS for normal classes or struct, and REFLECT_POLYMORPHIC_CLASS macro for the polymorphic classes and structs 
at the beginning of the class

i.e.
strcut Shape {
	REFLECT_CLASS(Shape)
};

struct Triangle : public Shape{
	REFLECT_POLYMORPHIC_CLASS(Triangle , Shape)
};

this will make you able to request the class size and name at run time 

Properties:
to add properties (member) into the class use 
PROPERTIES_BEGIN macro and PROPERTIES_END macro and add as many properties in 
between them as you wish using the PROPERTY macro
inside the property macro you can add setter and getters using the SETTER and GETTER macros

you can query the class members later and call the getter and setter and the 
member name, size and offset in the class (for POD)

i.e.

strcut Shape {
	REFLECT_CLASS(Shape)
	PROPERTIES_BEGIN
	PROPERTY(length)
	PROPERTY(width, SETTER(setWidth))
	PROPERTY(heigth, SETTER(setHeigth), GETTER(getHeigth))
	PROPERTIES_END

	void setWidth(int w){width = w;}
	
	int getHeigth(){ return heigth;}
	void setHeigth(int h){heigth = h;}
	
	int length, width, heigth;
};

Methods:
you can also register methods using the METHODS_BEGIN , METHOD and METHODS_END macros 
just like in the case of properties.

you can then query the method name and call it in run time as we will see.

i.e.

strcut Shape {
	REFLECT_CLASS(Shape)
	PROPERTIES_BEGIN
	PROPERTY(length)
	PROPERTY(width, SETTER(setWidth))
	PROPERTY(heigth, SETTER(setHeigth), GETTER(getHeigth))
	PROPERTIES_END


	METHODS_BEGIN
	METHOD(setWidth)
	METHOD(setHeigth)
	METHOD(getHeigth)
	METHODS_END

	void setWidth(int w){width = w;}
	
	int getHeigth(){ return heigth;}
	void setHeigth(int h){heigth = h;}
	
	int length, width, heigth;
};

using the library:

to query the metadata info of the object you can use either the reflection 
manager interface through the template function getMetadata or using a 
std::string or c style char * 
i.e.
auto metadata = ReflectionManager::getMetadata<Triangle>();
auto metadata = ReflectionManager::getInstance().getMetadataByName("Triangle")

when you get the metadata you can do things like calling a function: 
for (auto& method : metadata->getMethods()) {
  std::cout << method.getName() << std::endl;
  method.call<void>(t);
}

iterating over the members like:
for (auto& member : metadata->getMembers()) {
  std::cout << member.getName() << std::endl;
  member.getGetterMethod()->call<void>(t);
}
