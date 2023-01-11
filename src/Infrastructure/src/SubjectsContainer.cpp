#include<iostream>
#include<Observer.hpp>
/// @brief sdfsdfsdfdsf
//implemtnting dependency injection with rtti in the object class. Cataloguing objects
//well the subscriber knows the kind of object it will get data from, and what pdated state to expect
//maybe i can transfer the updated state in a normalized form, such as JSON.
//that just like in an api, the client and the server can work without knowing much on eachother
//use JSON internally
//Implemnt the pattern as a map, that maps subjects to observers
//we will end up with a graph
//overload the update method to pass many kinds of arguments
//you dont just send some data data between the observer and the subject just like you would using a REST API. The network here n
//reference an object using its object id. instead of its memory address.
//combining the subject and observer classes in the object class
//two objects should expect something from each other. Such key names in the JSON message.
//implment serialization and deserialization in the object class.
//Normally the getters will not be part of the subject interface.

//a observer need to know the type of its subject to execute the proper
//so we pass RTTI with update and use dynamic casting
//even with the object ould have to know the type of the subject or at least oe of its parents
//case class against observers
//different layers pf observer for different parts of the system, to respond to different kinds of functionalities
//manytypes of networks and connection managers for the scene, to exchange one know kind of data
//visual netork,
//position network
//input network
//updating a specific observer, graph7
//abstract factory for the many applications i can make
