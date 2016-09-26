#ifndef PMD_GEN_DATASUPPLIER_H
#define PMD_GEN_DATASUPPLIER_H

#include <QObject>
#include <QTimer>
#include <QtCore>
#include "pmd.h"
#include "pmdSupport.h"
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"

using namespace DDS;

typedef struct {
    unsigned short int index;
    signed short int ecgValue;
    signed short int abpValue;
    signed short int plethValue;
} pm_data_struct;

class PmdDatagen: public QObject
{
    Q_OBJECT

public:
    PmdDatagen(QObject * parent = 0);
    ~PmdDatagen();
    QList <unsigned int>  ecgData;
    QList <unsigned int>  abpData;
    QList <unsigned int>  plethData;

public slots:
    void updateData();
    void connectionStatus();

signals:
    void dataAvailable(pm_data_struct *);

private:
    unsigned int getECGData();
    unsigned int getABPData();
    unsigned int getPlethData();
	int publisher_shutdown(DomainParticipant *participant);

	pm_data_struct pm_data;
    QTimer *timer;
    int ecgIndex;
    int abpIndex;
    int plethIndex;
	DomainParticipant *participant;
    Publisher *publisher;
    Topic *topic;
	DataWriter *writer;
    InstanceHandle_t instance_handle;
	DataBus::pm_data_structDataWriter * pm_data_struct_writer;
	DataBus::pm_data_struct *instance;
	int domainId;
	const char *type_name;
	int retcode;
	QString argvString;
	int timer_interval;
};

#endif // PMD_GEN_DATASUPPLIER_H
