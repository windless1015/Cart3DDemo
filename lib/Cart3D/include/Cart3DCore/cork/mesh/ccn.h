#pragma once

#include <common/prelude.h>
#include <vector>


struct CCN
{
    //�����ָ����ṹ
    std::vector<std::vector<uint>> vv; 
    std::vector<std::vector<uint>> vf;
    const std::vector<Tri>& ref_tris;

    CCN(const std::vector<Tri>& tris);
};







