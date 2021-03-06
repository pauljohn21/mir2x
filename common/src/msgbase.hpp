/*
 * =====================================================================================
 *
 *       Filename: msgbase.hpp
 *        Created: 04/24/2017 00:46:48
 *    Description: length encoding for mode 1:
 *
 *                  [0 - 254]          : length in 0 ~ 254
 *                  [    255][0 ~ 255] : length as 0 ~ 255 + 255
 *              
 *                  1. most likely we are using 0 ~ 254
 *                  2. if compressed length more than 254 we need to bytes
 *                  3. we support range in [0, 255 + 255]
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#pragma once
#include <cstdint>
#include <cstddef>
#include "fflerror.hpp"
#include "msgattribute.hpp"

class MsgBase
{
    private:
        const uint8_t m_headCode;

    protected:
        MsgBase(uint8_t headCode)
            : m_headCode(headCode)
        {}

    public:
        int type() const
        {
            return getAttribute(m_headCode).type;
        }

        size_t dataLen() const
        {
            return getAttribute(m_headCode).dataLen;
        }

        size_t maskLen() const
        {
            if(type() == 1){
                return (dataLen() + 7) / 8;
            }
            throw fflerror("not compressed by xor");
        }

        const std::string &name() const
        {
            return getAttribute(m_headCode).name;
        }

    private:
        virtual const MsgAttribute &getAttribute(uint8_t) const = 0;
};
