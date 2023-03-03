#ifndef WORLDNODE_HPP
#define WORLDNODE_HPP

#include<Node.hpp>
class WorldNode : public Node
{

DECLARE_RTTI
private:
float clearColor[4];

public:
    WorldNode(float r, float g, float b, float a);
    void Draw(Camera* camera, float deltaTime) override;
    void setClearColor(float r, float g, float b, float a);

    ~WorldNode();
};



#endif