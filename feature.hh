/*
 * Feature.h
 *
 *  Created on: 28-sep-2009
 *      Author: mayte
 */

#ifndef FEATURE_H_
#define FEATURE_H_


#define MAX_OBS_FEATURES 100

#include <vector>
#include "scan.hh"
#include "types.hh"
#include "uloc.hh"

class Feature
{
public:
    /// Defaults to EDGE
    Feature(GeometricEntityKinds entity_kind);
    virtual ~Feature();

    double dimension() const;
    double codimension() const;
    const Transf& Loc() const;

    const Matrix& Cov() const;
    double Cov(int i, int j) const;
    void SetCov(const Matrix& c) { uloc_.SetCov(c); };

    const Uloc& uloc(void) const { return uloc_; };
    void set_uloc(const Uloc& u) { uloc_ = u; };

    void ComputeSegmentLength(Uloc p1, Uloc p2);

    void SetScan(const GuiSplit &split) { split_ = split; };
    // Keep the original raw data for debug
    const GuiSplit &GetScan(void) const { return split_; };
private:
    void GeometricRelationsObservationPointToPoint(Uloc Lsp1, Uloc Lsp2);

    double dimension_;
    double codimension_;
    Uloc   uloc_;

    GuiSplit split_;
};


class ObservedFeatures
{
public:
    ObservedFeatures();
    virtual ~ObservedFeatures();

    void AddObservedFeature(Feature f);
    int Count() const;
    //void SetPaired(int i, bool b);
    const Feature & features(int f) const;
    
    void Clear(void) { features_.clear(); }
    
private:
    vector<Feature> features_;
    vector<bool>    is_paired_;
};

void ScanDataSegmentation(const Scan &laser_raw_data, ObservedFeatures *feat_table);

#endif /* FEATURE_H_ */
