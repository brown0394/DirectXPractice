//***************************************************************************************
// RenderStates.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "RenderStates.h"

ID3D11RasterizerState* RenderStates::WireframeRS = 0;
ID3D11RasterizerState* RenderStates::NoCullRS    = 0;
	 
ID3D11BlendState*      RenderStates::AlphaToCoverageBS = 0;
ID3D11BlendState*      RenderStates::TransparentBS     = 0;
ID3D11BlendState*	   RenderStates::NonBlackBS		   = 0;
ID3D11DepthStencilState* RenderStates::NoDepthTestDSS  = 0;

void RenderStates::InitAll(ID3D11Device* device)
{
	//
	// WireframeRS
	//
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HR(device->CreateRasterizerState(&wireframeDesc, &WireframeRS));

	//
	// NoCullRS
	//
	D3D11_RASTERIZER_DESC noCullDesc;
	ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	noCullDesc.FillMode = D3D11_FILL_SOLID;
	noCullDesc.CullMode = D3D11_CULL_NONE;
	noCullDesc.FrontCounterClockwise = false;
	noCullDesc.DepthClipEnable = true;

	HR(device->CreateRasterizerState(&noCullDesc, &NoCullRS));

	//
	// AlphaToCoverageBS
	//

	D3D11_BLEND_DESC alphaToCoverageDesc = {0};
	alphaToCoverageDesc.AlphaToCoverageEnable = true;
	alphaToCoverageDesc.IndependentBlendEnable = false;
	alphaToCoverageDesc.RenderTarget[0].BlendEnable = false;
	alphaToCoverageDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(device->CreateBlendState(&alphaToCoverageDesc, &AlphaToCoverageBS));

	//
	// TransparentBS
	//

	D3D11_BLEND_DESC transparentDesc = {0};
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend       = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend      = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp        = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(device->CreateBlendState(&transparentDesc, &TransparentBS));

	D3D11_BLEND_DESC nonBlackDesc = { 0 };
	nonBlackDesc.AlphaToCoverageEnable = false;
	nonBlackDesc.IndependentBlendEnable = false;

	nonBlackDesc.RenderTarget[0].BlendEnable = true;
	nonBlackDesc.RenderTarget[0].SrcBlend			= D3D11_BLEND_SRC_ALPHA;
	nonBlackDesc.RenderTarget[0].DestBlend			= D3D11_BLEND_ONE;
	nonBlackDesc.RenderTarget[0].BlendOp			= D3D11_BLEND_OP_ADD;
	nonBlackDesc.RenderTarget[0].SrcBlendAlpha		= D3D11_BLEND_ZERO;
	nonBlackDesc.RenderTarget[0].DestBlendAlpha		= D3D11_BLEND_ZERO;
	nonBlackDesc.RenderTarget[0].BlendOpAlpha 		= D3D11_BLEND_OP_ADD;
	nonBlackDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HR(device->CreateBlendState(&nonBlackDesc, &NonBlackBS));


	D3D11_DEPTH_STENCIL_DESC noDepthTestDesc;
	noDepthTestDesc.DepthEnable = false;
	noDepthTestDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	noDepthTestDesc.DepthFunc = D3D11_COMPARISON_LESS;
	noDepthTestDesc.StencilEnable = false;
	noDepthTestDesc.StencilReadMask = 0xff;
	noDepthTestDesc.StencilWriteMask = 0xff;

	HR(device->CreateDepthStencilState(&noDepthTestDesc, &NoDepthTestDSS));
}

void RenderStates::DestroyAll()
{
	ReleaseCOM(WireframeRS);
	ReleaseCOM(NoCullRS);
	ReleaseCOM(AlphaToCoverageBS);
	ReleaseCOM(TransparentBS);
	ReleaseCOM(NonBlackBS);
	ReleaseCOM(NoDepthTestDSS);
}