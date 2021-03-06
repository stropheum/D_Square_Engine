#include "pch.h"
#include "CppUnitTest.h"
#include "LeakDetector.h"
#include "AttributedFoo.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibraryDesktop
{
    TEST_CLASS(AttributedTest)
    {

    public:

        TEST_METHOD_INITIALIZE(InitializeMethod)
        {
            LeakDetector::Initialize();
        }

        TEST_METHOD_CLEANUP(CleanupMethod)
        {
            LeakDetector::Finalize();
        }

        TEST_METHOD(TestConstructor)
        {
            Library::AttributedFoo myFoo;
            Assert::IsTrue(myFoo["this"] == static_cast<Library::RTTI*>(&myFoo));
        }

        TEST_METHOD(TestCopySemantics)
        {
            Library::AttributedFoo myFoo_OG;

            myFoo_OG["External Integer"] = 10;
            myFoo_OG["External Float"] = 10.0f;
            myFoo_OG["External Vector"] = glm::vec4(10);
            myFoo_OG["External Matrix"] = glm::mat4(10);
            myFoo_OG["External String"] = "10";

            for (std::int32_t i = 0; i < 10; i++)
            {	// Setting all values in the arrays to some default
                myFoo_OG["External Integer Array"].Set(10, i);
                myFoo_OG["External Float Array"].Set(10.0f, i);
                myFoo_OG["External Vector Array"].Set(glm::vec4(10), i);
                myFoo_OG["External Matrix Array"].Set(glm::mat4(10), i);
                myFoo_OG["External String Array"].Set("10", i);
            }

            Library::AttributedFoo myFoo_CPY(myFoo_OG);
            auto& myFooRef = myFoo_CPY["External Integer"];
            UNREFERENCED_PARAMETER(myFooRef);

            Assert::IsTrue(myFoo_OG["External Integer"] == myFoo_OG.m_int);
            Assert::IsTrue(myFoo_OG["External Float"] == myFoo_OG.m_float);
            Assert::IsTrue(myFoo_OG["External Vector"] == myFoo_OG.m_vector);
            Assert::IsTrue(myFoo_OG["External Matrix"] == myFoo_OG.m_matrix);
            Assert::IsTrue(myFoo_OG["External String"] == myFoo_OG.m_string);

            Assert::IsTrue(myFoo_CPY["External Integer"] == myFoo_OG.m_int);
            Assert::IsTrue(myFoo_CPY["External Float"] == myFoo_OG.m_float);
            Assert::IsTrue(myFoo_CPY["External Vector"] == myFoo_OG.m_vector);
            Assert::IsTrue(myFoo_CPY["External Matrix"] == myFoo_OG.m_matrix);
            Assert::IsTrue(myFoo_CPY["External String"] == myFoo_OG.m_string);

            Assert::IsTrue(myFoo_CPY["External Integer"] == myFoo_OG["External Integer"]);
            Assert::IsTrue(myFoo_CPY["External Float"] == myFoo_OG["External Float"]);
            Assert::IsTrue(myFoo_CPY["External Vector"] == myFoo_OG["External Vector"]);
            Assert::IsTrue(myFoo_CPY["External Matrix"] == myFoo_OG["External Matrix"]);
            Assert::IsTrue(myFoo_CPY["External String"] == myFoo_OG["External String"]);

            for (std::uint32_t i = 0; i < 10; i++)
            {
                Assert::IsTrue(myFoo_CPY["External Integer Array"].Get<std::int32_t>(i)
                    == myFoo_OG["External Integer Array"].Get<std::int32_t>(i));
                Assert::IsTrue(myFoo_CPY["External Float Array"].Get<float>(i)
                    == myFoo_OG["External Float Array"].Get<float>(i));
                Assert::IsTrue(myFoo_CPY["External Vector Array"].Get<glm::vec4>(i)
                    == myFoo_OG["External Vector Array"].Get<glm::vec4>(i));
                Assert::IsTrue(myFoo_CPY["External Matrix Array"].Get<glm::mat4>(i)
                    == myFoo_OG["External Matrix Array"].Get<glm::mat4>(i));
                Assert::IsTrue(myFoo_CPY["External String Array"].Get<std::string>(i)
                    == myFoo_OG["External String Array"].Get<std::string>(i));
            }
        }

        TEST_METHOD(TestMoveSemantics)
        {
            std::int32_t myInt = 10;
            float myFloat = 10.0f;
            glm::vec4 myVec(10);
            glm::mat4 myMat(10);
            std::string myStr("10");

            Library::AttributedFoo myFoo_OG;

            myFoo_OG["External Integer"] = myInt;
            myFoo_OG["External Float"] = myFloat;
            myFoo_OG["External Vector"] = myVec;
            myFoo_OG["External Matrix"] = myMat;
            myFoo_OG["External String"] = myStr;

            Library::AttributedFoo myFoo_CPY(std::move(myFoo_OG));

            Assert::IsTrue(myFoo_OG.Find("External Integer") == nullptr);
            Assert::IsTrue(myFoo_OG.Find("External Float") == nullptr);
            Assert::IsTrue(myFoo_OG.Find("External Vector") == nullptr);
            Assert::IsTrue(myFoo_OG.Find("External Matrix") == nullptr);
            Assert::IsTrue(myFoo_OG.Find("External String") == nullptr);

            Assert::IsTrue(myFoo_CPY["External Integer"] == myInt);
            Assert::IsTrue(myFoo_CPY["External Float"] == myFloat);
            Assert::IsTrue(myFoo_CPY["External Vector"] == myVec);
            Assert::IsTrue(myFoo_CPY["External Matrix"] == myMat);
            Assert::IsTrue(myFoo_CPY["External String"] == myStr);
        }

        TEST_METHOD(TestPopulate)
        {
            Library::AttributedFoo myFoo;

            Assert::IsTrue(myFoo[0] == myFoo["this"]);
            Assert::IsTrue(myFoo["External Integer"] == myFoo.m_int);
            Assert::IsTrue(myFoo["External Float"] == myFoo.m_float);
            Assert::IsTrue(myFoo["External Vector"] == myFoo.m_vector);
            Assert::IsTrue(myFoo["External Matrix"] == myFoo.m_matrix);
            Assert::IsTrue(myFoo["External String"] == myFoo.m_string);

            Assert::ExpectException<std::exception>([&] { myFoo[12]; });
        }

        TEST_METHOD(TestIsPrescribedAttribute)
        {
            Library::AttributedFoo myFoo;

            Assert::IsTrue(myFoo.IsPrescribedAttribute("External Integer"));
            Assert::IsTrue(myFoo.IsPrescribedAttribute("External Float"));
            Assert::IsTrue(myFoo.IsPrescribedAttribute("External Vector"));
            Assert::IsTrue(myFoo.IsPrescribedAttribute("External Matrix"));
            Assert::IsTrue(myFoo.IsPrescribedAttribute("External String"));
        }

        TEST_METHOD(TestIsAuxiliaryAttribute)
        {
            Library::AttributedFoo myFoo;
            Assert::IsFalse(myFoo.IsAttribute("Nothing"));
            myFoo.AppendAuxiliaryAttribute("Nothing");
            Assert::IsTrue(myFoo.IsAttribute("Nothing"));
            Assert::IsTrue(myFoo.IsAuxiliaryAttribute("Nothing"));
        }

        TEST_METHOD(TestIsAttribute)
        {
            Library::AttributedFoo myFoo;
            Assert::IsTrue(myFoo.IsAttribute("this"));
            Assert::IsTrue(myFoo.IsAttribute("External Integer"));
            Assert::IsTrue(myFoo.IsAttribute("External Float"));
            Assert::IsTrue(myFoo.IsAttribute("External Vector"));
            Assert::IsTrue(myFoo.IsAttribute("External Matrix"));
            Assert::IsTrue(myFoo.IsAttribute("External String"));

            Assert::IsFalse(myFoo.IsAttribute("Nonexistent Garbage"));
        }

        TEST_METHOD(TestAppendAuxiliaryAttribute)
        {
            Library::AttributedFoo myFoo;
            Assert::IsFalse(myFoo.IsAttribute("new"));

            myFoo.AppendAuxiliaryAttribute("new");
            Assert::IsTrue(myFoo.IsAttribute("new"));
        }
    };

}