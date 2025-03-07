# Copyright (c) 2020 vesoft inc. All rights reserved.
#
# This source code is licensed under Apache 2.0 License.

set(expression_test_common_libs
    $<TARGET_OBJECTS:parser_obj>
    $<TARGET_OBJECTS:ast_match_path_obj>
    $<TARGET_OBJECTS:expression_obj>
    $<TARGET_OBJECTS:ast_match_path_obj>
    $<TARGET_OBJECTS:network_obj>
    $<TARGET_OBJECTS:fs_obj>
    $<TARGET_OBJECTS:stats_obj>
    $<TARGET_OBJECTS:graph_stats_obj>
    $<TARGET_OBJECTS:meta_client_stats_obj>
    $<TARGET_OBJECTS:storage_client_stats_obj>
    $<TARGET_OBJECTS:datatypes_obj>
    $<TARGET_OBJECTS:time_obj>
    $<TARGET_OBJECTS:datetime_parser_obj>
    $<TARGET_OBJECTS:common_thrift_obj>
    $<TARGET_OBJECTS:thrift_obj>
    $<TARGET_OBJECTS:thread_obj>
    $<TARGET_OBJECTS:base_obj>
    $<TARGET_OBJECTS:function_manager_obj>
    $<TARGET_OBJECTS:wkt_wkb_io_obj>
    $<TARGET_OBJECTS:agg_function_manager_obj>
    $<TARGET_OBJECTS:meta_thrift_obj>
    $<TARGET_OBJECTS:graph_thrift_obj>
    $<TARGET_OBJECTS:storage_thrift_obj>
    $<TARGET_OBJECTS:meta_obj>
    $<TARGET_OBJECTS:meta_client_obj>
    $<TARGET_OBJECTS:conf_obj>
    $<TARGET_OBJECTS:charset_obj>
    $<TARGET_OBJECTS:file_based_cluster_id_man_obj>
    $<TARGET_OBJECTS:process_obj>
    $<TARGET_OBJECTS:time_utils_obj>
    $<TARGET_OBJECTS:ft_es_graph_adapter_obj>
    $<TARGET_OBJECTS:ws_common_obj>
    $<TARGET_OBJECTS:version_obj>
    $<TARGET_OBJECTS:graph_session_obj>
    $<TARGET_OBJECTS:graph_flags_obj>
    $<TARGET_OBJECTS:util_obj>
    $<TARGET_OBJECTS:expr_visitor_obj>
    $<TARGET_OBJECTS:graph_context_obj>
    $<TARGET_OBJECTS:plan_obj>
    $<TARGET_OBJECTS:idgenerator_obj>
    $<TARGET_OBJECTS:graph_obj>
    $<TARGET_OBJECTS:ssl_obj>
    $<TARGET_OBJECTS:memory_obj>
    $<TARGET_OBJECTS:gc_obj>
)


if(ENABLE_STANDALONE_VERSION)
set(expression_test_common_libs
    ${expression_test_common_libs}
    $<TARGET_OBJECTS:sa_test_graph_flags_obj>
)
endif()

nebula_add_library(
    expr_ctx_mock_obj OBJECT
    ExpressionContextMock.cpp
    TestBase.cpp
)

nebula_add_test(
    NAME
        expression_test
    SOURCES
        ExpressionTest.cpp
        EncodeDecodeTest.cpp
        AggregateExpressionTest.cpp
        ArithmeticExpressionTest.cpp
        AttributeExpressionTest.cpp
        CaseExpressionTest.cpp
        ColumnExpressionTest.cpp
        ConstantExpressionTest.cpp
        ContainerExpressionTest.cpp
        FunctionCallExpressionTest.cpp
        LabelExpressionTest.cpp
        ListComprehensionExpressionTest.cpp
        LogicalExpressionTest.cpp
        RelationalExpressionTest.cpp
        PathBuildExpressionTest.cpp
        PropertyExpressionTest.cpp
        PredicateExpressionTest.cpp
        ReduceExpressionTest.cpp
        SubscriptExpressionTest.cpp
        TypeCastingExpressionTest.cpp
        VersionedVariableExpressionTest.cpp
    OBJECTS
        $<TARGET_OBJECTS:expr_ctx_mock_obj>
        ${expression_test_common_libs}
    LIBRARIES
        gtest
        ${THRIFT_LIBRARIES}
        ${PROXYGEN_LIBRARIES}
)

nebula_add_executable(
    NAME
        expression_bm
    SOURCES
        ExpressionBenchmark.cpp
    OBJECTS
        $<TARGET_OBJECTS:expr_ctx_mock_obj>
        ${expression_test_common_libs}
    LIBRARIES
        follybenchmark
        boost_regex
        ${THRIFT_LIBRARIES}
        ${PROXYGEN_LIBRARIES}
)

nebula_add_executable(
    NAME
        func_call_expression_bm
    SOURCES
        FunctionCallExpressionBenchmark.cpp
    OBJECTS
        $<TARGET_OBJECTS:expression_obj>
        $<TARGET_OBJECTS:ast_match_path_obj>
        $<TARGET_OBJECTS:datatypes_obj>
        $<TARGET_OBJECTS:base_obj>
        $<TARGET_OBJECTS:expr_ctx_mock_obj>
        $<TARGET_OBJECTS:function_manager_obj>
        $<TARGET_OBJECTS:wkt_wkb_io_obj>
        $<TARGET_OBJECTS:time_obj>
        $<TARGET_OBJECTS:time_utils_obj>
        $<TARGET_OBJECTS:datetime_parser_obj>
        $<TARGET_OBJECTS:fs_obj>
        $<TARGET_OBJECTS:agg_function_manager_obj>
    LIBRARIES
        follybenchmark
        boost_regex
        ${THRIFT_LIBRARIES}
)

nebula_add_executable(
    NAME
        aggregate_expression_bm
    SOURCES
        AggregateExpressionBenchmark.cpp
    OBJECTS
        $<TARGET_OBJECTS:expression_obj>
        $<TARGET_OBJECTS:ast_match_path_obj>
        $<TARGET_OBJECTS:datatypes_obj>
        $<TARGET_OBJECTS:base_obj>
        $<TARGET_OBJECTS:expr_ctx_mock_obj>
        $<TARGET_OBJECTS:function_manager_obj>
        $<TARGET_OBJECTS:wkt_wkb_io_obj>
        $<TARGET_OBJECTS:agg_function_manager_obj>
        $<TARGET_OBJECTS:time_obj>
        $<TARGET_OBJECTS:time_utils_obj>
        $<TARGET_OBJECTS:datetime_parser_obj>
        $<TARGET_OBJECTS:fs_obj>
    LIBRARIES
        follybenchmark
        boost_regex
        ${THRIFT_LIBRARIES}
)
