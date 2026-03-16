#include "../parser.h"

int main(){
    params params = parse("input1.csv");

    bool passedalltests = true;

    int counter = 0;       

    cout << "Submissions: " << params.submissions.size() << "\n";
    for (submission sub : params.submissions){
        counter++;
        if (sub.id != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        if (sub.title != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        if (sub.name != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        if (sub.email != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        if (sub.primary != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
        if (sub.secondary != ) {cout << counter << ": Wrong sub ID: " << sub.id << endl; passedalltests = false;}
    }

    cout << "\n";

    counter = 0;

    cout << "Reviewers: " << params.reviewers.size() << "\n";
    for (reviewer rev : params.reviewers){
        if (rev.id != ) {cout << counter << ": Wrong sub ID: " << rev.id << endl; passedalltests = false;}
        if (rev.name != ) {cout << counter << ": Wrong sub ID: " << rev.id << endl; passedalltests = false;}
        if (rev.email != ) {cout << counter << ": Wrong sub ID: " << rev.id << endl; passedalltests = false;}
        if (rev.primary != ) {cout << counter << ": Wrong sub ID: " << rev.id << endl; passedalltests = false;}
        if (rev.secondary != ) {cout << counter << ": Wrong sub ID: " << rev.id << endl; passedalltests = false;}
    }

    cout << "\n";

    if (params.MinReviewsPerSubmission != ) {cout << "Wrong MinReviewsPerSubmission parameter: " << params.MinReviewsPerSubmission << endl; passedalltests = false;}

    if (params.MaxReviewsPerReviewer != ) {cout << "Wrong MaxReviewsPerReviewer parameter: " << params.MaxReviewsPerReviewer << endl; passedalltests = false;}

    if (params.PrimaryReviewerExpertise != ) {cout << "Wrong PrimaryReviewerExpertise parameter: " << params.PrimaryReviewerExpertise << endl; passedalltests = false;}

    if (params.SecondaryReviewerExpertise != ) {cout << "Wrong SecondaryReviewerExpertise parameter: " << params.SecondaryReviewerExpertise << endl; passedalltests = false;}  

    if (params.PrimarySubmissionDomain != ) {cout << "Wrong PrimarySubmissionDomain parameter: " << params.PrimarySubmissionDomain << endl; passedalltests = false;}

    if (params.SecondarySubmissionDomain != ) {cout << "Wrong SecondarySubmissionDomain parameter: " << params.SecondarySubmissionDomain << endl; passedalltests = false;} 

    cout << "\n";

    if (params.GenerateAssignments != ) {cout << "Wrong GenerateAssignments: " << params.GenerateAssignments << endl; passedalltests = false;}
    if (params.RiskAnalysis != ) {cout << "Wrong RiskAnalysis: " << params.RiskAnalysis << endl; passedalltests = false;}
    if (params.OutputFileName != ) {cout << "Wrong OutputFileName: " << params.OutputFileName << endl; passedalltests = false;}

    if (passedalltests){
        cout << "Test nº passed" << endl;
    }
    
    return 0;
}

