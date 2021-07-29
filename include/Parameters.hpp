/*
 * @Descripttion: 
 * @version: V0.1
 * @Author: Sean
 * @Date: 2021-07-25 15:53:42
 * @LastEditors: Sean
 * @LastEditTime: 2021-07-29 20:46:40
 */


#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

namespace GenLas {
    
    class Parameter {
    public:

        static Parameter& instance() {
            static Parameter m_instance;
            return m_instance;
        }

        void SetLidar2body(  const Eigen::Matrix<double, 3, 3>& rotate,
                    const Eigen::Matrix<double, 3, 1>& translate,
                    const Eigen::Matrix<double, 3, 1>& check_angle) {
            m_trans = Eigen::Transform<double, 3, Eigen::Affine>::Identity();
            m_trans.rotate(rotate);
            m_trans.translate(translate);
            m_trans.rotate(Eigen::AngleAxisd(check_angle(0, 0), Eigen::Vector3d(1, 0, 0)));
            m_trans.rotate(Eigen::AngleAxisd(check_angle(1, 0), Eigen::Vector3d(0, 1, 0)));
            m_trans.rotate(Eigen::AngleAxisd(check_angle(2, 0), Eigen::Vector3d(0, 0, 1)));
        }

        Eigen::Transform<double, 3, Eigen::Affine>& getTrans() {
            return m_trans;
        }

    private:
        Parameter() {}
        
        Eigen::Transform<double, 3, Eigen::Affine> m_trans;
    };

    int setPara(std::string parameter_file) {
        // use https://github.com/pulzed/mINI.git
        //std::string parameter_file = "parameter.ini";
        mINI::INIFile file(parameter_file);
        mINI::INIStructure ini;
        
        if (file.read(ini) == false) {
            LOG(ERROR) << "parameter.ini read false! \n";
            throw("parameter ini file read false\n");
            return 0;
        }
        
        std::string matrix = ini["rotate"]["matrix"];
        std::vector<double> data;
        std::regex re(",");
        std::vector<std::string> matrix_s(std::sregex_token_iterator(matrix.begin(), matrix.end(), re, -1),
                                        std::sregex_token_iterator());
        if (matrix_s.size() != 9) {
            LOG(ERROR) << "rotate matrix: decode error!\n";
            return 0;
        }

        Eigen::Matrix<double, 3, 3> rotate_matrix = Eigen::Matrix<double, 3, 3>::Zero();
        for (int i = 0; i < 9; ++i)
            rotate_matrix(i) = std::stod(matrix_s[i]);

        Eigen::Matrix<double, 3, 1> trans_arm = Eigen::Matrix<double, 3, 1>::Zero();
        trans_arm(0, 0) = std::stod(ini["trans"]["x"]);
        trans_arm(1, 0) = std::stod(ini["trans"]["y"]);
        trans_arm(2, 0) = std::stod(ini["trans"]["z"]);

        Eigen::Matrix<double, 3, 1> angle_check = Eigen::Matrix<double, 3, 1>::Zero();
        angle_check(0, 0) = std::stod(ini["check angle"]["roll"]);
        angle_check(1, 0) = std::stod(ini["check angle"]["pitch"]);
        angle_check(2, 0) = std::stod(ini["check angle"]["heading"]);
        
        GenLas::Parameter::instance().SetLidar2body(rotate_matrix, trans_arm, angle_check);
    }
};
