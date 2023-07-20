#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;
layout(location = 5) in ivec4 boneIds; 
layout(location = 6) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 TexCoords;
//apparently, the animation matrices, in the  case of this model, affect the scale aswell.

void main()
{
    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >=MAX_BONES)//making sure the index of the bone is not out of range.
        {//if ine bone id is out of range, we skip all the animation for this vertex.
            totalPosition = vec4(pos,1.0f);
            break;
        }
        vec4 localPosition = vec4(pos,1.0f);
        //if(25<boneIds[i] && boneIds[i]<=50  /*boneIds[i]!=68*/){
        localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0f);
        //}
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;//even the normals are modified by 
        //the animation, should do the same for the tangent and bitangent.
   }
	//we do the animation in model space.
    //total position gives us the final vertex position in model space.
    //we then proceed normally
    //we could put the animation code in a separate function.
    mat4 viewModel = view * model;
    gl_Position =  projection * viewModel * vec4(totalPosition.xyz*0.01, 1.0);
	//gl_Position =  projection * viewModel * vec4(pos*0.01, 1.0f);
	TexCoords = tex;
}
//matrix 18 seems to be a culprit
