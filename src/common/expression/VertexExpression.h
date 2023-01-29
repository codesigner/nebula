/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#ifndef COMMON_EXPRESSION_VERTEXEXPRESSION_H_
#define COMMON_EXPRESSION_VERTEXEXPRESSION_H_

#include "common/expression/Expression.h"

namespace nebula {

/**
 * This is an internal type of expression to denote a Vertex value.
 * It has no corresponding rules in parser.
 * It is generated from LabelExpression during semantic analysis
 * and expression rewrite.
 */
class VertexExpression final : public Expression {
 public:
  // default name : VERTEX, $^ : startNode of EDGE, $$ : endNode of EDGE
  // $$ & $^ only used in go sentence
  static VertexExpression *make(ObjectPool *pool, const nebula::String &name = "VERTEX") {
    return pool->makeAndAdd<VertexExpression>(pool, name);
  }

  const Value &eval(ExpressionContext &ctx) override;

  void accept(ExprVisitor *visitor) override;

  Expression *clone() const override {
    return VertexExpression::make(pool_, name());
  }

  nebula::String toString() const override {
    return name_;
  }

  const nebula::String &name() const {
    return name_;
  }

  bool operator==(const Expression &expr) const override;

 private:
  friend ObjectPool;
  VertexExpression(ObjectPool *pool, const nebula::String &name)
      : Expression(pool, Kind::kVertex), name_(name) {}

  void writeTo(Encoder &encoder) const override;

  void resetFrom(Decoder &) override;

 private:
  nebula::String name_;
  Value result_;
};

}  // namespace nebula

#endif  // COMMON_EXPRESSION_VERTEXEXPRESSION_H_
