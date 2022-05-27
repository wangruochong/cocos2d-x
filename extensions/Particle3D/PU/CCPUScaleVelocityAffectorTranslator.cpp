/****************************************************************************
 Copyright (C) 2013 Henry van Merode. All rights reserved.
 Copyright (c) 2015-2017 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCPUScaleVelocityAffectorTranslator.h"
#if CC_USE_3D_PARTICLE
#include "extensions/Particle3D/PU/CCPUParticleSystem3D.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttribute.h"
#include "extensions/Particle3D/PU/CCPUDynamicAttributeTranslator.h"

NS_CC_BEGIN

PUScaleVelocityAffectorTranslator::PUScaleVelocityAffectorTranslator()
{
}
//-------------------------------------------------------------------------
bool PUScaleVelocityAffectorTranslator::translateChildProperty( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUPropertyAbstractNode* prop = reinterpret_cast<PUPropertyAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(prop->parent->context);
    PUScaleVelocityAffector* affector = static_cast<PUScaleVelocityAffector*>(af);

    if (prop->name == token[TOKEN_SCALE_VELOCITY_SCALE])
    {
        // Property: velocity_scale
        if (passValidateProperty(compiler, prop, token[TOKEN_SCALE_VELOCITY_SCALE], VAL_REAL))
        {
            float val = 0.0f;
            if(getFloat(*prop->values.front(), &val))
            {
                PUDynamicAttributeFixed* dynamicAttributeFixed = new (std::nothrow) PUDynamicAttributeFixed();
                dynamicAttributeFixed->setValue(val);
                affector->setDynScaleVelocity(dynamicAttributeFixed);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_SINCE_START_SYSTEM])
    {
        // Property: since_start_system
        if (passValidateProperty(compiler, prop, token[TOKEN_SINCE_START_SYSTEM], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setSinceStartSystem(val);
                return true;
            }
        }
    }
    else if (prop->name == token[TOKEN_STOP_AT_FLIP])
    {
        // Property: stop_at_flip
        if (passValidateProperty(compiler, prop, token[TOKEN_STOP_AT_FLIP], VAL_BOOL))
        {
            bool val;
            if(getBoolean(*prop->values.front(), &val))
            {
                affector->setStopAtFlip(val);
                return true;
            }
        }
    }

    return false;
}

bool PUScaleVelocityAffectorTranslator::translateChildObject( PUScriptCompiler* compiler, PUAbstractNode *node )
{
    PUObjectAbstractNode* child = reinterpret_cast<PUObjectAbstractNode*>(node);
    PUAffector* af = static_cast<PUAffector*>(child->parent->context);
    PUScaleVelocityAffector* affector = static_cast<PUScaleVelocityAffector*>(af);

    PUDynamicAttributeTranslator dynamicAttributeTranslator;
    if (child->cls == token[TOKEN_SCALE_VELOCITY_SCALE])
    {
        // Property: velocity_scale
        dynamicAttributeTranslator.translate(compiler, node);
        PUDynamicAttribute* dynamicAttribute = static_cast<PUDynamicAttribute*>(child->context);
        affector->setDynScaleVelocity(dynamicAttribute);
        return true;
    }

    return false;
}

NS_CC_END
#endif
