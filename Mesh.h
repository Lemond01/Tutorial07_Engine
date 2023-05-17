#pragma once

#include <d3d11.h>
#include <xnamath.h>
#include <vector>
#include "Structures.h"

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT3 normal;
    XMFLOAT2 texCoord;
};

class Mesh
{
public:
    Mesh(ID3D11Device* device, const std::vector<SimpleVertex>& vertices, const std::vector<WORD>& indices, ID3D11Buffer* vB, ID3D11Buffer* iB);
    ~Mesh();

    void Render(ID3D11DeviceContext* context);
    UINT getVertexCount() { return m_vertexCount; }
    
private:
    void CreateVertexBuffer(ID3D11Device* device, const std::vector<SimpleVertex>& vertices);
    void CreateIndexBuffer(ID3D11Device* device, const std::vector<WORD>& indices);

    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;
    UINT m_vertexCount;
    UINT m_indexCount;
};