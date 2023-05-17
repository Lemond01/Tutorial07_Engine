#pragma once

#include <d3d11.h>
#include <xnamath.h>
#include <vector>

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT3 normal;
    XMFLOAT2 texCoord;
};

class Mesh
{
public:
    Mesh(ID3D11Device* device, const std::vector<Vertex>& vertices, const std::vector<WORD>& indices);
    ~Mesh();

    void Render(ID3D11DeviceContext* context);

private:
    void CreateVertexBuffer(ID3D11Device* device, const std::vector<Vertex>& vertices);
    void CreateIndexBuffer(ID3D11Device* device, const std::vector<WORD>& indices);

    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;
    UINT m_vertexCount;
    UINT m_indexCount;
};