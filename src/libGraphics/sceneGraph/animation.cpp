#include<animation.h>
#include<AssetManager.hpp>

IMPLEMENT_RTTI(Animation, Object)


void Animation::load(Stream& stream)
{
    Object::load(stream);
}
void Animation::save(Stream& stream)
{
    //what if you try to^perform this op on a path that is already relative

    stream.writeln(TYPE.GetName());
    string relativePath = AssetManager::getInstance()->getSplitPathUsingBasePath(animationPath);
    stream.writeln(relativePath);
    Object::save(stream);

}
