#include<cassert>
#include<chrono>
#include "../include/group.h"


Group::Group(const std::vector<ull>& _group, const OperationRules op, const ull mod) {
    m_group = _group;
    m_op = op;
    m_mod = mod;
    m_identity = 0;

    assert(init());

}

void Group::print_group() {

    int isize = m_group.size();
    if (isize == 0) {
        std::cout << "Empty group." << std::endl;
        return ;
    }

    std::cout << "Element of current group: " << std::endl;
    for(int i = 0; i < isize; ++i) {
        std::cout << m_group[i] << " ";
    }

    std::cout << std::endl;

    std::cout << "Group identity: " << m_identity << std::endl;
}

 template<typename T>
void Group::print_vector(std::vector<T>& vec) {

    for(int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}
    
bool Group::init() {

    assert(check_group_element());
    assert(is_closure());
    assert(is_associativity());
    assert(exist_identity_element());
    assert(exist_inverse_lement());

    return  true;
}

bool Group::check_group_element() {

    long isize = m_group.size();
    if (m_op == OperationRules::Modulo) {
        for(long i = 0; i < isize; ++i) {
            if (m_group[i] >= m_mod) {
                return false;
            }
        }
    }

    return true;
}

bool Group::is_closure() {
    
    int isize = m_group.size();

    std::cout << "op: " << m_op << std::endl;

    switch (m_op)
    {
        case OperationRules::addition: {
            
            if(!check_closure_by_addition()) {
                return false;
            }

            break;
        } 
        case OperationRules::Multiplication: {
            if(!check_closure_by_multiplication()) {
                return false;
            }

            break;
        }
        case OperationRules::Modulo: {
            if(!check_closure_by_modulo()) {
                return false;
            } 

            break;
        }
        default: {
            return false;
        }
       
    }

    return true;
}


        
bool Group::is_associativity() {
    int isize = m_group.size();

    switch (m_op)
    {
    case OperationRules::addition: {
        
        if(!check_associativity_by_addition()) {
            return false;
        }
        break;
    } 
    case OperationRules::Multiplication: {
         if(!check_associativity_by_multiplication()) {
            return false;
        }

        break;
    }
    case OperationRules::Modulo: {
         if(!check_associativity_by_modulo()) {
            return false;
        }

        break;
    }
    
    default:

        return false;
    }

    return true;
}



bool Group::exist_identity_element() {
    
    switch (m_op)
    {
    case OperationRules::addition: {
        
   
        break;
    } 
    case OperationRules::Multiplication: {
   

        break;
    }
    case OperationRules::Modulo: {
         if(!find_element_by_modulo()) {
            return false;
        }

        break;
    }
    
    default:

        return false;
    }

    return true;
}

// 查找单位元，暂时没有考虑集合中是否存大多个单位元的情况，这也是不符合群的定义的；
bool Group::find_element_by_modulo() {

    long isize = m_group.size();

    if (isize == 0) {
        return false;
    }

    if (isize == 1) {
        const long e = m_group[0];

        if (e * e % m_mod == e) {
            m_identity = e;
            return true;
        } else {
            return false;
        }

    }

    long e = m_group[0];
    long temp = 0;
    long e_index = 0;
    for(long i = 1; i < isize; ++i) {

        temp = e * m_group[i] % m_mod;

        /*
            结果会用三种情况：
                1. temp == e: 第二个元素有可能就是单位元，更新 e 为第二个元素； 
                2. temp == m_group： 第一个有可能是单位元，继续检查；
                3. 都不相等，说明当前 e 和当前元素都不是单位元， 则需要跳转一个元素，同时防止数据溢出;
        */ 
        if(temp  == e ) {
            e = m_group[i];
            e_index = i;

        } else if (temp == m_group[i]) {
            
        } else {   
            
            i = i + 1;
            if (i < isize) {
                e = m_group[i];
                e_index = i;
            }
        }

        if (e_index == isize) {
            return false;
        }
    }



    // 需要对前面的元素进行检测
    for(long i = 1; i < e_index; ++i) {
        temp = e * m_group[i] % m_mod;
        if (temp != e) {
            return false;
        }
    }

    //更新单位元
    m_identity = e;

    std::cout << "e: " << e << ", e_index: "<< e_index << std::endl;

    return true;
}

// 集合中的元素是否都有逆元
bool Group::exist_inverse_lement() {

    long isize = m_group.size();

    bool is_find = false;
    for(long i = 0; i < isize ; ++i)  {
        is_find = false;
        for(long j = 0; j < isize; ++j) {
            if (m_group[i] * m_group[j] % m_mod == 1) {
                is_find = true;
                continue;
            }
        }

        if (!is_find) {
            return false;
        }
    }
        
    std::cout << "exist_inverse_lement success." << std::endl;
    return true;
}

ErrorCode Group::get_subgroup(std::vector<std::vector<ull>>& subgroups) {


    return ErrorCode::Success;
}


bool Group::is_element_in_group(const ull& v) {
    
    int isize = m_group.size();

    for(int i = 0; i < isize; ++i) {
        if (v == m_group[i]) {
            return true;
        }
    }

    return false;
}



// 子群的检验：
// 1. 拉格朗日定理：如果G是一个有限群，H是G的一个子群，则必有 H的阶整除 G的阶。注意，这是一个充分不必要条件，即它的逆定理不一定成立;
// 2.如果 H 是 G 的子群，则必须满足条件：对于H中的任意两个元素(这两个元素也必须在G中)，则元素 (a OP b的逆元) 必须也在H 中； 
bool Group::is_subgroup(const std::vector<ull>& _group) {

    
    return true;
}



bool Group::check_closure_by_addition() {

    int isize = m_group.size();

    for( int i = 0; i < isize; ++i) 
        for(int j = i + 1; j < isize; ++j) {
            if(!is_element_in_group(m_group[i] + m_group[j])) {
                return false;
            }
        }

    return true;
}

bool Group::check_closure_by_multiplication() {
    int isize = m_group.size();

    for( int i = 0; i < isize; ++i) 
        for(int j = i + 1; j < isize; ++j) {
            if(!is_element_in_group(m_group[i] * m_group[j])) {
                return false;
            }
        }

    return true;
}

bool Group::check_closure_by_modulo() {
    int isize = m_group.size();
    for( int i = 0; i < isize; ++i) {
        if(!is_element_in_group(m_group[i] % m_mod)) {
            return false;
        }
    }

    std::cout << " check_closure_by_modulo  success." << std::endl;
    return true;
}

// 检查群中所有元素都满足交换律是一个繁琐的任务，我们这里打算简化处理
// 采用随机抽取元素进行多轮检查即可，其它类似的情况都按这种方法简化处理
bool Group::check_associativity_by_addition() {

    // pass
    return true;
}

bool Group::check_associativity_by_multiplication() {
    
    //  pass
    return true;
}

// 
bool Group::check_associativity_by_modulo() {

    const int isize = m_group.size();
    std::pair<long, long>  range(0, isize);
    const long amount = 3;
    std::vector<long> rand_indexs;

    for(long i = 0; i < Max_Check_times; ++i) {
        rand_indexs.clear();
        genrate_random_number(range, amount, rand_indexs);

        // 虽然模运算支持加法的结合律，但是好像不能满足群的定义，我们这里只验证 整数模 N 的乘法群;
        // if (!check_ssociativity_by_modulo_addition(rand_indexs)) {
        //     return false;
        // }
        if (!check_ssociativity_by_modulo_Multiplication(rand_indexs)) {
            return false;
        }
    }
    std::cout << "check_associativity_by_modulo success. " << std::endl;
    return true;
}

// 加法结合律： ((a+b)%p+c)%p=(a+(b+c)%p)%p 
bool Group::check_ssociativity_by_modulo_addition(const std::vector<long>& indexs) {

    assert(indexs.size() == 3);
    const long a = m_group[indexs[0]];
    const long b = m_group[indexs[1]];
    const long c = m_group[indexs[2]];

    return ((a + b) % m_mod + c ) % m_mod == ( a + ( b + c ) % m_mod ) % m_mod ;
}

// 乘法结合律:  ((a*b)%p * c)%p= (a * (b*c)%p)%p
bool Group::check_ssociativity_by_modulo_Multiplication(const std::vector<long>& indexs) {

    assert(indexs.size() == 3);
    const long a = m_group[indexs[0]];
    const long b = m_group[indexs[1]];
    const long c = m_group[indexs[2]];

    return (((a * b) % m_mod * c) % m_mod == (a * ( b * c ) % m_mod) % m_mod);
}



void Group::genrate_random_number(const std::pair<long,long>& range, const long& amount, std::vector<long>& randoms) {

    for(long i = 0; i < amount; ++i) {
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());;
        std::uniform_int_distribution<long> distribution(range.first, range.second);
   
        randoms.push_back(distribution(gen));
    }
    return ;
}