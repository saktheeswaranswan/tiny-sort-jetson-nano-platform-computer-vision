/*
 * @Author: zerollzeng
 * @Date: 2019-08-29 15:45:15
 * @LastEditors: zerollzeng
 * @LastEditTime: 2019-08-29 17:34:29
 */
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "Trt.h"

// PYBIND11_MAKE_OPAQUE(std::vector<float>);
using vector_f = std::vector<float>;
PYBIND11_MAKE_OPAQUE(vector_f);

PYBIND11_MODULE(pytrt, m) {
    m.doc() = "python interface of tiny-tensorrt";
    pybind11::class_<TrtPluginParams>(m, "TrtPluginParams")
        .def(pybind11::init<>());
    pybind11::class_<Trt>(m, "Trt")
        .def(pybind11::init([]() {
            return std::unique_ptr<Trt>(new Trt());
        }))
        .def(pybind11::init([](TrtPluginParams params) { 
            return std::unique_ptr<Trt>(new Trt(params));
        }))
        .def("CreateEngine", (void (Trt::*)(const std::string&,
                                            const std::string&,
                                            const std::string&,
                                            const std::vector<std::string>&,
                                            const std::vector<std::vector<float>>&,
                                            int,
                                            int)) &Trt::CreateEngine, "create engine with caffe model")
        .def("CreateEngine", (void (Trt::*)(const std::string&,
                                            const std::string&,
                                            int)) &Trt::CreateEngine, "create engine with onnx model")
        .def("Forward", (void (Trt::*)()) &Trt::Forward)
        .def("DataTransfer", (void (Trt::*)(std::vector<float>&, int, bool)) &Trt::DataTransfer, "transfer data between host and device");
        ;
}