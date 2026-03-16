#include "../parser.h"

int main(){
    params params = parse("dataset7.csv");

    cout << "Submissions: " << params.submissions.size() << "\n";
    for (submission sub : params.submissions){
        cout << sub.id << " + " << sub.title << " + " << sub.name << " + " << sub.email << " + " << sub.primary << " + " << sub.secondary << "\n";
    }

    cout << "\n";

    cout << "Reviewers: " << params.reviewers.size() << "\n";
    for (reviewer rev : params.reviewers){
        cout << rev.id << " + " << rev.name << " + " << rev.email << " + " << rev.primary << " + " << rev.secondary << "\n";
    }

    cout << "\n";

    cout << "Parameters: " << endl;
    cout << "MinReviewsPerSubmission: " << params.MinReviewsPerSubmission << endl;
    cout << "MaxReviewsPerReviewer: " << params.MaxReviewsPerReviewer << endl;
    cout << "PrimaryReviewerExpertise: " << params.PrimaryReviewerExpertise << endl;
    cout << "SecondaryReviewerExpertise: " << params.SecondaryReviewerExpertise << endl;
    cout << "PrimarySubmissionDomain: " << params.PrimarySubmissionDomain << endl;
    cout << "SecondarySubmissionDomain: " << params.SecondarySubmissionDomain << endl;

    cout << "\n";

    cout << "Control: " << endl;
    cout << "GenerateAssignments: " << params.GenerateAssignments << endl;
    cout << "RiskAnalysis: " << params.RiskAnalysis << endl;
    cout << "OutputFileName: " << params.OutputFileName << endl;
    
    return 0;
}

