#include "zfc_interfaces/capture.hpp"
#include <gtest/gtest.h>
#include <thread>
TEST(Capture, OverflowCompletionDoesNotDependOnPlotPublication) {
  zfc::Capture<2> capture;
  ASSERT_TRUE(capture.begin(42));
  zfc::Snapshot s;
  for (int i=0;i<5;++i) { s.measured.time_ns=i; capture.append(s); }
  s.phase=zfc::Phase::complete;
  capture.append(s); // Terminal sample itself overflows.
  capture.finish(true);
  EXPECT_EQ(capture.drops(),4U);
  zfc::Completion final;
  EXPECT_FALSE(capture.completion(final));
  zfc::CaptureRecord record;
  ASSERT_TRUE(capture.pop(record));
  EXPECT_EQ(record.sequence,1U);
  ASSERT_TRUE(capture.pop(record));
  EXPECT_EQ(record.sequence,2U);
  EXPECT_FALSE(capture.pop(record));
  ASSERT_TRUE(capture.completion(final));
  EXPECT_EQ(final.final.trial_id,42U);
  EXPECT_EQ(final.final.sequence,6U);
  EXPECT_EQ(final.final.state.phase,zfc::Phase::complete);
  EXPECT_EQ(final.dropped,4U);
  EXPECT_TRUE(final.completed);
  EXPECT_FALSE(capture.completion(final));
  ASSERT_TRUE(capture.begin(43));
  capture.append({});
  capture.finish(false);
  ASSERT_TRUE(capture.pop(record));
  EXPECT_EQ(record.sequence,1U);
  EXPECT_EQ(record.trial_id,43U);
  ASSERT_TRUE(capture.completion(final));
  EXPECT_EQ(final.dropped,0U);
  EXPECT_FALSE(final.completed);
}
TEST(Capture, ConcurrentSequenceIntegrity) {
  zfc::Capture<4096> queue;
  ASSERT_TRUE(queue.begin(1));
  std::thread producer([&] {
    for (int i=0;i<2000;++i) queue.append({});
    queue.finish(true);
  });
  std::uint64_t count=0;
  zfc::CaptureRecord r;
  zfc::Completion terminal;
  while (!queue.completion(terminal)) {
    if (queue.pop(r)) EXPECT_EQ(r.sequence,++count);
    else std::this_thread::yield();
  }
  producer.join();
  EXPECT_EQ(count,2000U);
  EXPECT_EQ(terminal.final.sequence,count);
  EXPECT_EQ(terminal.dropped,0U);
}
