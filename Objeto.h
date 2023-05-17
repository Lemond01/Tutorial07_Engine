#pragma once
#include "Mesh.h"

class Objeto
{
public:
    Objeto(ID3D11Device* device, ID3D11DeviceContext* context);
    ~Objeto();

    void Update(float deltaTime);
    void Render(ID3D11DeviceContext* context, ID3D11Buffer* _g_pCBChangesEveryFrame);
private:
    Mesh* m_mesh;
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;
    XMFLOAT3 m_scale;
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;
};






