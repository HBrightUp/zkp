#pragma once

#include<iostream>
#include<vector>
#include<random>
#include<utility>
#include "../../common/include/common.h"
#include "../../common/include/errorcode.h"


// 随机抽样检查的次数。很多定义或者定理要求群中的所有元素满足某个条件，但考虑到如果群中的数据宠大，这显然对群进行完全性的检查是
//  一个艰巨的任务，我们的妥协协的办法是进行随机抽样检查：如果检查的数据都符合某个定理，则认为群中的所有元素都满足此定理 ;
const ull Max_Check_times = 10;

// 二元运算法则
enum OperationRules {
    addition,       // 加法
    Multiplication,     // 乖法
    Modulo,         //  求余运算
};


enum ClassifyGroup {
    FiniteGroup,    // 有限群
    InfiniteGroup,  // 无限群
    OrdinaryGroup,  // 平凡群 
    Subgroup,       // 子群
};


class Group{    

    public:
        Group(const std::vector<ull>& _group, const OperationRules op, const ull mod = 5);

        bool init();

        void print_group();

        template<typename T>
        void print_vector(std::vector<T>& vec);
    
    
    public:

        // 获取当前群的所有子群
        ErrorCode get_subgroup(std::vector<std::vector<ull>>& subgroups);

        // 给定一个群，查看它是当前群的子群
        bool is_subgroup(const std::vector<ull>& _group);


    private:
        bool check_group_element();

        // 检查某个元素是否存在于群中
        bool is_element_in_group(const ull& v);

        // 检查元素的封闭性
        bool check_closure(const ull& a, const ull& b);
        bool check_closure_by_addition();
        bool check_closure_by_multiplication();
        bool check_closure_by_modulo();

        
        // 判断是否有封闭性
        bool is_closure();
        bool check_associativity_by_addition();
        bool check_associativity_by_multiplication();
        
        bool check_associativity_by_modulo();

        // 查找群的交单位元，此群是一个 modulo 类型
        bool find_element_by_modulo();

        // 判断元素是否满足结合率
        bool check_ssociativity_by_modulo_addition(const std::vector<long>& indexs); 
        bool check_ssociativity_by_modulo_Multiplication(const std::vector<long>& indexs);

        // 在给定区间产生一个随机数
        void genrate_random_number(const std::pair<long,long>& range, const long& amount, std::vector<long>& randoms);
      

        // 判断是否满足结合律
        bool is_associativity();

         // 是否存在单位元
        bool exist_identity_element();

        // 是否存在逆元
        bool exist_inverse_lement();

    private:

        // 单位元
        int m_identity;

        // 群的元素集合
        std::vector<ull> m_group;

        // 二次运算的方法
        OperationRules m_op;

        // 模运算 
        ull m_mod;

   
        

};
