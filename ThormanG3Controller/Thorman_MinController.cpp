/**
   @author Shin'ichiro Nakaoka
*/

#include <cnoid/SimpleController>
#include <vector>

using namespace cnoid;

const double pgain[35]={1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
                        1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
                        1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
                        1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
                        1000.0, 1000.0, 1000.0, 1000.0, 0,
                        1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
                        1000.0, 0,      1000.0, 1000.0, 1000.0};

const double dgain[35]={50.0, 50.0, 50.0, 50.0, 50.0,
                        50.0, 50.0, 50.0, 50.0, 50.0,
                        50.0, 50.0, 50.0, 50.0, 50.0,
                        50.0, 50.0, 50.0, 50.0, 50.0,
                        50.0, 50.0, 50.0, 50.0, 0.0,
                        50.0, 50.0, 50.0, 50.0, 50.0,
                        50.0, 0.0, 50.0, 50.0, 50.0};

class Thorman_MinController : public SimpleController
{
    BodyPtr ioBody;
    double dt;
    std::vector<double> qref;
    std::vector<double> qold;

public:

    virtual bool initialize(SimpleControllerIO* io) override
    {
        ioBody = io->body();
        dt = io->timeStep();

        for(int i=0; i < ioBody->numJoints(); ++i){
            Link* joint = ioBody->joint(i);
            joint->setActuationMode(Link::JOINT_TORQUE);
            io->enableIO(joint);
            qref.push_back(joint->q());
        }
        qold = qref;

        return true;
    }

    virtual bool control() override
    {
        for(int i=0; i < ioBody->numJoints(); ++i){
            Link* joint = ioBody->joint(i);
            double q = joint->q();
            double dq = (q - qold[i]) / dt;
            double u = (qref[i] - q) * pgain[i] + (0.0 - dq) * dgain[i];
            qold[i] = q;
            joint->u() = u;
        }
        return true;
    }
};

CNOID_IMPLEMENT_SIMPLE_CONTROLLER_FACTORY(Thorman_MinController)
