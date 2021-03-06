#ifndef TEST_CLASS_H_
#define TEST_CLASS_H_
/**
 * \file testClass.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from test.xml
 */

#include "core/reflection/reflection.h"
#include "core/reflection/defaultSetter.h"
#include "core/reflection/printerVisitor.h"

/*
 *  Embed includes.
 */
/*
 *  Additional includes for Composite Types.
 */
#include "testSubClass.h"

// using namespace corecvs;

/*
 *  Additional includes for Pointer Types.
 */

// namespace corecvs {
// }
/*
 *  Additional includes for enum section.
 */
#include "testEnum.h"
#include "testEnum.h"

/**
 * \brief Test Class with no practical use 
 * Test Class with no practical use 
 **/
class TestClass : public corecvs::BaseReflection<TestClass>
{
public:
    enum FieldId {
        BOOL_FIELD_ID,
        INT_FIELD0_ID,
        INT_FIELD1_ID,
        INT_FIELD2_ID,
        DOUBLE_FIELD0_ID,
        DOUBLE_FIELD1_ID,
        STRING_FIELD_ID,
        WSTRING_FIELD_ID,
        ENUM_FIELD0_ID,
        ENUM_FIELD1_ID,
        VECTOR_FIELD0_ID,
        VECTOR_FIELD1_ID,
        SUBCLASS_FIELD_ID,
        TEST_CLASS_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief Bool Field 
     * Bool Field 
     */
    bool mBoolField;

    /** 
     * \brief Int Field0 
     * Int Field0 
     */
    int mIntField0;

    /** 
     * \brief Int Field1 
     * Int Field1 
     */
    int mIntField1;

    /** 
     * \brief Int Field2 
     * Int Field2 
     */
    int mIntField2;

    /** 
     * \brief Double field0 
     * Double field0 
     */
    double mDoubleField0;

    /** 
     * \brief Double field1 
     * Double field1 
     */
    double mDoubleField1;

    /** 
     * \brief String field 
     * String field 
     */
    std::string mStringField;

    /** 
     * \brief WString field 
     * WString field 
     */
    std::wstring mWStringField;

    /** 
     * \brief Enum Field0 
     * Enum Field0 
     */
    int mEnumField0;

    /** 
     * \brief Enum Field1 
     * Enum Field1 
     */
    int mEnumField1;

    /** 
     * \brief Vector Field0 
     * Vector Field0 
     */
    vector<double> mVectorField0;

    /** 
     * \brief Vector Field1 
     * Vector Field1 
     */
    vector<double> mVectorField1;

    /** 
     * \brief Subclass Field 
     * Subclass Field 
     */
    TestSubClass mSubclassField;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit(corecvs::Reflection *toFill);

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    bool boolField() const
    {
        return mBoolField;
    }

    int intField0() const
    {
        return mIntField0;
    }

    int intField1() const
    {
        return mIntField1;
    }

    int intField2() const
    {
        return mIntField2;
    }

    double doubleField0() const
    {
        return mDoubleField0;
    }

    double doubleField1() const
    {
        return mDoubleField1;
    }

    std::string stringField() const
    {
        return mStringField;
    }

    std::wstring wStringField() const
    {
        return mWStringField;
    }

    TestEnum::TestEnum enumField0() const
    {
        return static_cast<TestEnum::TestEnum>(mEnumField0);
    }

    TestEnum::TestEnum enumField1() const
    {
        return static_cast<TestEnum::TestEnum>(mEnumField1);
    }

    vector<double> vectorField0() const
    {
        return mVectorField0;
    }

    vector<double> vectorField1() const
    {
        return mVectorField1;
    }

    TestSubClass subclassField() const
    {
        return mSubclassField;
    }

    /* Section with setters */
    void setBoolField(bool boolField)
    {
        mBoolField = boolField;
    }

    void setIntField0(int intField0)
    {
        mIntField0 = intField0;
    }

    void setIntField1(int intField1)
    {
        mIntField1 = intField1;
    }

    void setIntField2(int intField2)
    {
        mIntField2 = intField2;
    }

    void setDoubleField0(double doubleField0)
    {
        mDoubleField0 = doubleField0;
    }

    void setDoubleField1(double doubleField1)
    {
        mDoubleField1 = doubleField1;
    }

    void setStringField(std::string stringField)
    {
        mStringField = stringField;
    }

    void setWStringField(std::wstring wStringField)
    {
        mWStringField = wStringField;
    }

    void setEnumField0(TestEnum::TestEnum enumField0)
    {
        mEnumField0 = enumField0;
    }

    void setEnumField1(TestEnum::TestEnum enumField1)
    {
        mEnumField1 = enumField1;
    }

    void setVectorField0(vector<double> vectorField0)
    {
        mVectorField0 = vectorField0;
    }

    void setVectorField1(vector<double> vectorField1)
    {
        mVectorField1 = vectorField1;
    }

    void setSubclassField(TestSubClass const &subclassField)
    {
        mSubclassField = subclassField;
    }

    /* Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mBoolField,                 static_cast<const corecvs::BoolField *>(fields()[BOOL_FIELD_ID]));
        visitor.visit(mIntField0,                 static_cast<const corecvs::IntField *>(fields()[INT_FIELD0_ID]));
        visitor.visit(mIntField1,                 static_cast<const corecvs::IntField *>(fields()[INT_FIELD1_ID]));
        visitor.visit(mIntField2,                 static_cast<const corecvs::IntField *>(fields()[INT_FIELD2_ID]));
        visitor.visit(mDoubleField0,              static_cast<const corecvs::DoubleField *>(fields()[DOUBLE_FIELD0_ID]));
        visitor.visit(mDoubleField1,              static_cast<const corecvs::DoubleField *>(fields()[DOUBLE_FIELD1_ID]));
        visitor.visit(mStringField,               static_cast<const corecvs::StringField *>(fields()[STRING_FIELD_ID]));
        visitor.visit(mWStringField,              static_cast<const corecvs::WStringField *>(fields()[WSTRING_FIELD_ID]));
        visitor.visit((int &)mEnumField0,         static_cast<const corecvs::EnumField *>(fields()[ENUM_FIELD0_ID]));
        visitor.visit((int &)mEnumField1,         static_cast<const corecvs::EnumField *>(fields()[ENUM_FIELD1_ID]));
        visitor.visit(mVectorField0,              static_cast<const corecvs::DoubleVectorField *>(fields()[VECTOR_FIELD0_ID]));
        visitor.visit(mVectorField1,              static_cast<const corecvs::DoubleVectorField *>(fields()[VECTOR_FIELD1_ID]));
        visitor.visit(mSubclassField,             static_cast<const corecvs::CompositeField *>(fields()[SUBCLASS_FIELD_ID]));
    }

    TestClass()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    TestClass(
          bool boolField
        , int intField0
        , int intField1
        , int intField2
        , double doubleField0
        , double doubleField1
        , std::string stringField
        , std::wstring wStringField
        , TestEnum::TestEnum enumField0
        , TestEnum::TestEnum enumField1
        , vector<double> vectorField0
        , vector<double> vectorField1
        , TestSubClass subclassField
    )
    {
        mBoolField = boolField;
        mIntField0 = intField0;
        mIntField1 = intField1;
        mIntField2 = intField2;
        mDoubleField0 = doubleField0;
        mDoubleField1 = doubleField1;
        mStringField = stringField;
        mWStringField = wStringField;
        mEnumField0 = enumField0;
        mEnumField1 = enumField1;
        mVectorField0 = vectorField0;
        mVectorField1 = vectorField1;
        mSubclassField = subclassField;
    }

    bool operator ==(const TestClass &other) const 
    {
        if ( !(this->mBoolField == other.mBoolField)) return false;
        if ( !(this->mIntField0 == other.mIntField0)) return false;
        if ( !(this->mIntField1 == other.mIntField1)) return false;
        if ( !(this->mIntField2 == other.mIntField2)) return false;
        if ( !(this->mDoubleField0 == other.mDoubleField0)) return false;
        if ( !(this->mDoubleField1 == other.mDoubleField1)) return false;
        if ( !(this->mStringField == other.mStringField)) return false;
        if ( !(this->mWStringField == other.mWStringField)) return false;
        if ( !(this->mEnumField0 == other.mEnumField0)) return false;
        if ( !(this->mEnumField1 == other.mEnumField1)) return false;
        if ( !(this->mVectorField0 == other.mVectorField0)) return false;
        if ( !(this->mVectorField1 == other.mVectorField1)) return false;
        if ( !(this->mSubclassField == other.mSubclassField)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, TestClass &toSave)
    {
        corecvs::PrinterVisitor printer(out);
        toSave.accept<corecvs::PrinterVisitor>(printer);
        return out;
    }

    void print ()
    {
        std::cout << *this;
    }
};
#endif  //TEST_CLASS_H_
