#include "OSGFMesh.h"
#include <fstream>
#include "ShaderConstants.h"
using namespace std;
OSGFMesh::OSGFMesh(Game&game,ID3DX10Mesh* mesh,std::string effect,
	std::string tech, const MaterialContainer& mtrlContainer)
		:OSGF3DDrawableComponent(game),mEffect(effect,game.GetDevice()),
		 mMaterials(mtrlContainer)
{
		mEffect.SetTechique(tech);
		mMesh = mesh;
		mMesh->AddRef();
		const D3D10_INPUT_ELEMENT_DESC* d;
		UINT u;
		mMesh->GetVertexDescription(&d,&u);
		mEffect.CreateInputLayout(d,u);
		
}
void OSGFMesh::Render()const
{
		OSGF3DDrawableComponent::Render();
		ID3D10EffectShaderResourceVariable* var = 
			mEffect.GetVariableAsShaderResource("gText");
		D3DXMATRIX* m = const_cast<D3DXMATRIX*>(&GetWVPMatrix());
		mEffect.SetMatrix(OSGF_FX_WORLD_VIEW_PROJECTION,m);
		mEffect.SetVector("eyePos",(FLOAT*)&(GetCamera()->GetPosition()));
		D3D10_TECHNIQUE_DESC techDesc;
		ID3D10EffectTechnique* tech = mEffect.GetEffectTechnique();
		HR(tech->GetDesc(&techDesc));
		UINT nSubsets;
		mMesh->GetAttributeTable(NULL,&nSubsets);
		mEffect.SetVector(OSGF_FX_LIGHT_AMBIENT,(FLOAT*)&GetLight()->ambientLight);
		mEffect.SetVector(OSGF_FX_LIGHT_DIFFUSE,(FLOAT*)&GetLight()->diffuseLight);
		mEffect.SetVector(OSGF_FX_LIGHT_SPECULAR,(FLOAT*)&GetLight()->specularLight);
		mEffect.SetVector(OSGF_FX_LIGHT_POSINTION,(FLOAT*)&GetLight()->lightPos);
		for(UINT subsetID = 0; subsetID < nSubsets; ++subsetID)
			{
				if(mMaterials.Size()>subsetID)
				{
					const Material& mtrl = mMaterials[subsetID];
					var->SetResource(mtrl.texture);
					mEffect.SetVector(OSGF_FX_MATERIAL_AMBIENT,(FLOAT*)&mtrl.ambient);
					mEffect.SetVector(OSGF_FX_MATERIAL_DIFFUSE,(FLOAT*)&mtrl.diffuse);
					mEffect.SetVector(OSGF_FX_MATERIAL_SPECULAR,(FLOAT*)&mtrl.specular);
				}
				for(UINT i = 0; i < techDesc.Passes; ++i)
				{
					ID3D10EffectPass* pass = tech->GetPassByIndex(i);
					/*mfxReflectMtrlVar->SetRawValue((void*)&mReflectMtrls[subsetID], 0, sizeof(D3DXVECTOR3));
						mfxDiffuseMapVar->SetResource(mDiffuseTextures[subsetID]);
						mfxSpecMapVar->SetResource(mSpecTextures[subsetID]);
						mfxNormalMapVar->SetResource(mNormalTextures[subsetID]);

						mfxCubeMapEnabledVar->SetBool(false);*/

						HR(pass->Apply(0));
						HR(mMesh->DrawSubset(subsetID));
			
				}
				
			}
		
}
void OSGFMesh::Copy(const OSGFMesh& m)
{
		mEffect = m.mEffect;
		mMesh = m.mMesh;
		mMesh->AddRef();
		mMaterials = m.mMaterials;
}