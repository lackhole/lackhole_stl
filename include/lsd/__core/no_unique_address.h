//
// Created by yonggyulee on 2024/01/04.
//

#ifndef LSD_CORE_NO_UNIQUE_ADDRESS_H_
#define LSD_CORE_NO_UNIQUE_ADDRESS_H_

#if __cplusplus < 202002L
#define LSD_NO_UNIQUE_ADDRESS
#else
#define LSD_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

#endif // LSD_CORE_NO_UNIQUE_ADDRESS_H_