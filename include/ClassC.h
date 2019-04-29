#ifndef TESTLIB_EXT_CLASSC_H_
#define TESTLIB_EXT_CLASSC_H_

#include "ClassA.h"

namespace TestLib
{
    namespace Ext
    {
        class ClassC : Base::ClassA
        {
        public:
            ClassC();
            virtual ~ClassC();

            void meth3();

            void update();
        };
    }
}

#endif /* TESTLIB_EXT_CLASSC_H_ */
