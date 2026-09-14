import tempfile
import unittest
from pathlib import Path
from fixture import generate
from trace import read_trace, load_run, cm_partition, summary

class TraceTest(unittest.TestCase):
    def test_fixture_partition_and_statistics(self):
        with tempfile.TemporaryDirectory() as tmp:
            generate(tmp)
            d,m,i=load_run(Path(tmp)/'synthetic-cm')
            self.assertTrue(m['synthetic'])
            self.assertEqual(i['records'],12)
            self.assertEqual(i['trace_drops'],0)
            self.assertEqual(i['missing_cycles'],0)
            self.assertTrue(cm_partition(d).sum(axis=1).eq(d.sleep_entry-d.cycle_entry).all())
            self.assertTrue(d.active_span_ns.eq(23000).all())
            self.assertEqual(summary(d.active_span_ns)['maximum'],23000)
            self.assertFalse(d.deadline_miss.any())
            self.assertGreater(d.period_error_ns.max(),0) # A long period is NOT a deadline miss.
    def test_corruption_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            generate(tmp); p=Path(tmp)/'synthetic-cm/timing.bin'; data=p.read_bytes()
            for altered in (data[:5],data[:-1],data+b'0',b'wrong!!!'+data[8:]):
                p.write_bytes(altered)
                with self.assertRaises(ValueError): read_trace(p)
    def test_unknown_deadline_remains_unknown(self):
        with tempfile.TemporaryDirectory() as tmp:
            generate(tmp); d,_,_=load_run(Path(tmp)/'synthetic-cm')
            d['deadline_mono_ns']=0
            from trace import metrics
            d=metrics(d)
            self.assertTrue(d.deadline_miss.isna().all())
if __name__=='__main__': unittest.main()
