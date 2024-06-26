//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* **                                                                      ** */
/* ** This file is generated by a script.                                  ** */
/* **                                                                      ** */
/* ** Do not edit it directly (unless it is within a CUSTOM CODE section)! ** */
/* ** Edit hdGen/schema.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#ifndef PXR_IMAGING_HD_BASIS_CURVES_SCHEMA_H
#define PXR_IMAGING_HD_BASIS_CURVES_SCHEMA_H

#include "pxr/imaging/hd/api.h"

#include "pxr/imaging/hd/basisCurvesTopologySchema.h"
#include "pxr/imaging/hd/geomSubsetsSchema.h"


// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

//-----------------------------------------------------------------------------

// --(BEGIN CUSTOM CODE: Declares)--
// --(END CUSTOM CODE: Declares)--

//-----------------------------------------------------------------------------

#define HD_BASIS_CURVES_SCHEMA_TOKENS \
    (basisCurves) \
    (topology) \
    (geomSubsets) \

TF_DECLARE_PUBLIC_TOKENS(HdBasisCurvesSchemaTokens, HD_API,
    HD_BASIS_CURVES_SCHEMA_TOKENS);

//-----------------------------------------------------------------------------
class HdBasisCurvesSchema : public HdSchema
{
public:
    HdBasisCurvesSchema(HdContainerDataSourceHandle container)
    : HdSchema(container) {}

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

    //ACCESSORS


    HD_API
    HdBasisCurvesTopologySchema GetTopology();

    HD_API
    HdGeomSubsetsSchema GetGeomSubsets();

    // RETRIEVING AND CONSTRUCTING

    /// Builds a container data source which includes the provided child data
    /// sources. Parameters with nullptr values are excluded. This is a
    /// low-level interface. For cases in which it's desired to define
    /// the container with a sparse set of child fields, the Builder class
    /// is often more convenient and readable.
    HD_API
    static HdContainerDataSourceHandle
    BuildRetained(
        const HdContainerDataSourceHandle &topology,
        const HdContainerDataSourceHandle &geomSubsets
    );

    /// \class HdBasisCurvesSchema::Builder
    /// 
    /// Utility class for setting sparse sets of child data source fields to be
    /// filled as arguments into BuildRetained. Because all setter methods
    /// return a reference to the instance, this can be used in the "builder
    /// pattern" form.
    class Builder
    {
    public:
        HD_API
        Builder &SetTopology(
            const HdContainerDataSourceHandle &topology);
        HD_API
        Builder &SetGeomSubsets(
            const HdContainerDataSourceHandle &geomSubsets);

        /// Returns a container data source containing the members set thus far.
        HD_API
        HdContainerDataSourceHandle Build();

    private:
        HdContainerDataSourceHandle _topology;
        HdContainerDataSourceHandle _geomSubsets;
    };

    /// Retrieves a container data source with the schema's default name token
    /// "basisCurves" from the parent container and constructs a
    /// HdBasisCurvesSchema instance.
    /// Because the requested container data source may not exist, the result
    /// should be checked with IsDefined() or a bool comparison before use.
    HD_API
    static HdBasisCurvesSchema GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer);

    /// Returns a token where the container representing this schema is found in
    /// a container by default.
    HD_API
    static const TfToken &GetSchemaToken();

    /// Returns an HdDataSourceLocator (relative to the prim-level data source)
    /// where the container representing this schema is found by default.
    HD_API
    static const HdDataSourceLocator &GetDefaultLocator();

    // DATA SOURCE LOCATORS FOR MEMBERS
    //
    // The following methods return an HdDataSourceLocator (relative to the
    // prim-level data source) where the data source for a member can be found.
    //
    // This is often useful for checking intersection against the
    // HdDataSourceLocatorSet sent with HdDataSourceObserver::PrimsDirtied.


    /// Prim-level relative data source locator to locate topology.
    HD_API
    static const HdDataSourceLocator &GetTopologyLocator();

    /// Prim-level relative data source locator to locate geomSubsets.
    HD_API
    static const HdDataSourceLocator &GetGeomSubsetsLocator();


};

PXR_NAMESPACE_CLOSE_SCOPE

#endif