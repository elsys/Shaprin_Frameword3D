#include "OSGF3DModel.h"
#include "Game.h"
#include "Util.h"
using namespace std;

OSGF3DModel::OSGF3DModel( Game& game,const string& mEffect,
	const string& technique)
	:OSGF3DDrawableComponent(game),
	mEffectName(mEffect),mTechName(technique)

{
	mPrimitiveTopology=D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}
void OSGF3DModel::Initialize()
{
	if(IsInitialized())return;
	OSGF3DDrawableComponent::Initialize();
	mEffect = new Effect(mEffectName,mGame.GetDevice());
	mEffect -> SetTechique(mTechName);
}
void OSGF3DModel::Render()const
{
	OSGF3DDrawableComponent::Render();
	if(!mIndexBuffer||(UINT)mIndexBuffer==0xcdcdcdcd)
		throw exception("Index buffer not created");
	if(!mVertexBuffer||(UINT)mVertexBuffer==0xcdcdcdcd)
		throw exception("Vertex buffer not created");
	ID3D10Device* dev = mGame.GetDevice(); 
	UINT offset = 0;
	ID3D10EffectShaderResourceVariable* var = 
			mEffect->GetVariableAsShaderResource("gText");
	var->SetResource(const_cast<ID3D10ShaderResourceView*>(mText));
	dev->IASetVertexBuffers(0,1,&mVertexBuffer,&mVertexSize,&offset);
	dev->IASetIndexBuffer(mIndexBuffer,DXGI_FORMAT_R32_UINT,0);
	dev->IASetPrimitiveTopology(mPrimitiveTopology);
	dev->IASetInputLayout(mEffect->GetVertexLayout());
	mEffect->SetMatrix("gWVP",const_cast<D3DXMATRIX*>(&GetWVPMatrix()));
	D3D10_TECHNIQUE_DESC techDesc;
	ID3D10EffectTechnique * tech = mEffect->GetEffectTechnique();
	tech->GetDesc(&techDesc);
	for(UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex( p )->Apply(0);
		dev->DrawIndexed(mNIndices,0,0);
	}
}
void OSGF3DModel::CreateVertexBuffer(void* verts,UINT bufferSize,UINT vertexSize,UINT CPUAccessFlags,
	UINT miscFlags,D3D10_USAGE usage)
{
	this->mVertexSize = vertexSize;
	D3D10_BUFFER_DESC desc;
	desc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	desc.ByteWidth = bufferSize;
	desc.CPUAccessFlags = CPUAccessFlags;
	desc.MiscFlags = miscFlags;
	desc.Usage = usage;
	D3D10_SUBRESOURCE_DATA subResource;
	ZeroMemory(&subResource,sizeof(subResource));
	subResource.pSysMem = verts;
	HR(mGame.GetDevice()->CreateBuffer(&desc,&subResource,&mVertexBuffer));
}
void OSGF3DModel::CreateIndexBuffer(DWORD indices[],UINT size,UINT CPUAccessFlags,
	UINT miscFlags,D3D10_USAGE usage)
{
	mNIndices = size/sizeof(DWORD);
	D3D10_BUFFER_DESC desc;
	desc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	desc.ByteWidth = size;
	desc.CPUAccessFlags = CPUAccessFlags;
	desc.MiscFlags = miscFlags;
	desc.Usage = usage;
	D3D10_SUBRESOURCE_DATA iInitData;
	ZeroMemory(&iInitData,sizeof(D3D10_SUBRESOURCE_DATA));
	iInitData.pSysMem = indices;
	HR(mGame.GetDevice()->CreateBuffer(&desc,&iInitData,&mIndexBuffer));
}
void OSGF3DModel::SetTexture(const std::string& file)
{
	SafeDelete(mText);
	HR(D3DX10CreateShaderResourceViewFromFileA(mGame.GetDevice(),
		file.c_str(),NULL,NULL,&mText,NULL));
	mTextName = file;
}
OSGF3DModel::~OSGF3DModel(void)
{
	delete mEffect;
	ReleaseCom(mVertexBuffer);
	ReleaseCom(mIndexBuffer);
}
