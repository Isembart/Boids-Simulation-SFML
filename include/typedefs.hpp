#pragma once
#include <memory>

class gameObject;
class quadTree;
class particle;

// typedef gameObject* gameObjectPtr;
typedef std::shared_ptr<gameObject> gameObjectPtr;
typedef std::shared_ptr<quadTree> quadTreePtr;
typedef std::shared_ptr<particle> particlePtr;